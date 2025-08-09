import argparse
import xml.etree.ElementTree as ET
import os


def generate_cracker(root: ET, output_dir: str, name: str):

    fix_version = f"FIX{root.attrib['major']}{root.attrib['minor']}"
    fix_version_lower = f"fix{root.attrib['major']}{root.attrib['minor']}"
    namespace = f"{fix_version}::{name}"
    ns_name = name

    messages = root.find("messages")
    if messages is None:
        raise ValueError("No <messages> section found in the XML.")

    message_classes = []
    for message in messages.findall("message"):
        msg_name = message.attrib["name"]
        msg_type = message.attrib["msgtype"]
        message_classes.append((msg_name, msg_type))

    # Construct final output path
    output_path = os.path.join(output_dir, ns_name, fix_version_lower)
    os.makedirs(output_path, exist_ok=True)
    header_path = os.path.join(output_path, "MessageCracker.hpp")

    lines = []

    # Header guard and includes
    lines.append("#pragma once\n")
    lines.append("#include <quickfix/Message.h>")
    lines.append("#include <quickfix/SessionID.h>\n")

    # Forward declarations
    lines.append(f"namespace {namespace} {{")
    for msg_name, _ in message_classes:
        lines.append(f"    class {msg_name};")
    lines.append("}\n")

    # MessageCracker class
    lines.append(f"namespace {namespace} {{\n")
    lines.append("class MessageCracker {")
    lines.append("public:")

    for msg_name, _ in message_classes:
        lines.append(f"    virtual void onMessage(const {namespace}::{msg_name}& message, const FIX::SessionID& sessionID) {{}}")

    lines.append("")
    lines.append("    void crack(const FIX::Message& message, const FIX::SessionID& sessionID) {")
    lines.append("        const std::string& msgType = message.getHeader().getField(FIX::FIELD::MsgType);")

    for msg_name, msg_type in message_classes:
        lines.append(
            f"        if (msgType == \"{msg_type}\") return onMessage((const {namespace}::{msg_name}&)message, sessionID);"
        )

    lines.append("        throw FIX::UnsupportedMessageType();")
    lines.append("    }")

    lines.append("};")
    lines.append("\n} // namespace")

    # Save to file
    with open(header_path, "w") as f:
        f.write("\n".join(lines))

    print(f"✅ MessageCracker.hpp generated at: {header_path}")


FIELD_TYPE_MACROS = {
    "STRING": "DEFINE_STRING",
    "INT": "DEFINE_INT",
    "LENGTH": "DEFINE_LENGTH",
    "DATA": "DEFINE_DATA",
    "FLOAT": "DEFINE_FLOAT",
    "PRICE": "DEFINE_PRICE",
    "QTY": "DEFINE_QTY",
    "CURRENCY": "DEFINE_CURRENCY",
    "BOOLEAN": "DEFINE_BOOLEAN",
    "CHAR": "DEFINE_CHAR",
    "SEQNUM": "DEFINE_SEQNUM",
    "UTCTIMESTAMP": "DEFINE_UTCTIMESTAMP",
    "UTCTIMEONLY": "DEFINE_UTCTIMEONLY",
    "UTCDATE": "DEFINE_UTCDATE",
    "NUMINGROUP":"DEFINE_NUMINGROUP"
}

def generate_fix_fields(root: ET, output_dir: str, name: str):

    fields = root.find("fields")
    if fields is None:
        raise ValueError("No <fields> section found in the XML.")

    namespace = name
    ns_path = os.path.join(output_dir, namespace)
    os.makedirs(ns_path, exist_ok=True)

    output_path = os.path.join(ns_path, "FixFields.hpp")

    lines = []
    lines.append("#pragma once\n")
    lines.append('#include <quickfix/Field.h>\n')
    lines.append('#include "FieldMacros.h"\n')
    lines.append('#include "FixFieldNumbers.h"\n')

    lines.append("namespace FIX {\n")

    for field in fields.findall("field"):
        fieldName = field.attrib["name"]
        type_ = field.attrib["type"].upper()
        macro = FIELD_TYPE_MACROS.get(type_)

        if not macro:
            print(f"⚠️ Skipping unsupported type '{type_}' for field '{fieldName}'")
            continue

        lines.append(f"  {macro}({name}, {fieldName});")

    lines.append("\n} // namespace FIX")

    with open(output_path, "w") as f:
        f.write("\n".join(lines))

    print(f"✅ FixFields.hpp generated at: {output_path}")



def generate_field_numbers(root: ET, output_dir: str, name: str):

    fields = root.find("fields")
    if fields is None:
        raise ValueError("No <fields> section found in the XML.")

    namespace = name
    ns_path = os.path.join(output_dir, namespace)
    os.makedirs(ns_path, exist_ok=True)

    output_path = os.path.join(ns_path, "FixFieldNumbers.h")

    lines = []
    lines.append("#pragma once\n")
    lines.append(f"namespace FIX::FIELD::{name}"+" {")

    for field in fields.findall("field"):
        fieldName = field.attrib["name"]
        number = field.attrib["number"]
        lines.append(f"    const int {fieldName} = {number};")

    lines.append("}")

    with open(output_path, "w") as f:
        f.write("\n".join(lines))

    print(f"✅ FixFieldNumbers.h generated at: {output_path}")


def generate_fix_values(root: ET.Element, output_dir: str, name: str):
    # FIX version, e.g. FIX.4.4
    fix_version_str = f"FIX.{root.attrib['major']}.{root.attrib['minor']}"

    lines = []
    written_constants = set()  # Track already-defined variable names

    lines.append("#pragma once\n")
    lines.append('#include <string>')
    lines.append(f"namespace FIX::{name}\n"+"{")

    # Add FIX version
    const_name = f"BeginString_{fix_version_str.replace('.', '')}"
    if const_name not in written_constants:
        lines.append(f'  const char BeginString_FIX{root.attrib["major"]}{root.attrib["minor"]}[] = "{fix_version_str}";')
        written_constants.add(const_name)

    # Message types
    for message in root.findall(".//messages/message"):
        msgName = message.attrib.get("name")
        msgtype = message.attrib.get("msgtype")
        if msgName and msgtype:
            const_name = f"MsgType_{msgName}"
            if const_name not in written_constants:
                if len(msgtype) == 1:
                    lines.append(f'  const char {const_name} = \'{msgtype}\';')
                else:
                    lines.append(f'  const char {const_name}[] = "{msgtype}";')
                written_constants.add(const_name)

    # Enumerated values
    for field in root.findall(".//fields/field"):
        field_name = field.attrib.get("name")
        for value in field.findall("value"):
            enum_val = value.attrib.get("enum")
            enum_desc = value.attrib.get("description")
            if enum_val and enum_desc:
                safe_enum_desc = enum_desc.upper().replace(" ", "_").replace("-", "_").replace("/", "_")
                const_name = f"{field_name}_{safe_enum_desc}"
                if const_name not in written_constants:
                    if len(enum_val) == 1:
                        lines.append(f'  const char {const_name} = \'{enum_val}\';')
                    else:
                        lines.append(f'  const char {const_name}[] = "{enum_val}";')
                    written_constants.add(const_name)

    lines.append("}")

    # Output directory for namespace
    ns_path = os.path.join(output_dir, name)
    os.makedirs(ns_path, exist_ok=True)

    output_path = os.path.join(ns_path, "FixValues.h")
    with open(output_path, "w") as f:
        f.write("\n".join(lines))

    print(f"✅ FixValues.h generated at: {output_path}")


def generate_fix_messages(root: ET.Element, output_dir: str, name: str):
    fix_version = f"FIX{root.attrib['major']}{root.attrib['minor']}"
    fix_version_lower = f"fix{root.attrib['major']}{root.attrib['minor']}"
    namespace = f"{fix_version}::{name}"

    messages = root.find("messages")
    if messages is None:
        raise ValueError("No <messages> section found in the XML.")

    fields = root.find("fields")
    if fields is None:
        raise ValueError("No <fields> section found in the XML.")

    # Map field name → number
    field_numbers = {f.attrib["name"]: int(f.attrib["number"]) for f in fields.findall("field")}

    # Map component name -> component element
    comps_root = root.find("components")
    components = {}
    if comps_root is not None:
        for c in comps_root.findall("component"):
            components[c.attrib["name"]] = c

    namespace_path = os.path.join(output_dir, name)
    fix_version_path = os.path.join(namespace_path, fix_version_lower)
    os.makedirs(fix_version_path, exist_ok=True)

    # Expand children of a message/group/component into a flat ordered list of items.
    # Each item is either ('field', field_name) or ('group', group_name, group_element).
    def expand_children(elem: ET.Element, seen_components: set | None = None):
        if seen_components is None:
            seen_components = set()

        items = []
        for child in list(elem):
            if child.tag == "field":
                items.append(("field", child.attrib["name"]))
            elif child.tag == "group":
                # keep the group element so we can recurse later
                items.append(("group", child.attrib["name"], child))
            elif child.tag == "component":
                comp_name = child.attrib["name"]
                if comp_name in seen_components:
                    raise ValueError(f"Circular component include detected: {comp_name}")
                comp_elem = components.get(comp_name)
                if comp_elem is None:
                    raise ValueError(f"Component '{comp_name}' referenced but not found in <components>.")
                # expand the component's children in-place, passing updated seen_components
                items.extend(expand_children(comp_elem, seen_components | {comp_name}))
            else:
                # ignore unknown tags (or optionally raise)
                continue
        return items

    # helper: get the first field number inside a group (digging into components / nested groups)
    def get_first_field_number_of_group_elem(g_elem: ET.Element):
        items = expand_children(g_elem)
        for it in items:
            if it[0] == "field":
                fname = it[1]
                if fname not in field_numbers:
                    raise KeyError(f"Field '{fname}' not found in <fields>.")
                return field_numbers[fname]
            elif it[0] == "group":
                # recursion for nested groups
                return get_first_field_number_of_group_elem(it[2])
        raise ValueError(f"Group '{g_elem.attrib.get('name')}' contains no fields (cannot determine first field).")

    # Recursively generate a group class from a <group> element
    def generate_group_class(group_elem: ET.Element, indent: int = 4):
        lines = []
        spaces = " " * indent
        group_name = group_elem.attrib["name"]
        if group_name not in field_numbers:
            raise KeyError(f"Group/NumInGroup '{group_name}' not found in <fields> section.")
        group_tag = field_numbers[group_name]

        # expand this group's children (fields / nested groups / components)
        items = expand_children(group_elem)

        # compute first field number (for delimiter)
        first_field_num = get_first_field_number_of_group_elem(group_elem)

        # build message_order: for each item, include either field number (field) or
        # the nested group's first-field-number (delim) (group)
        msg_order_nums = []
        for it in items:
            if it[0] == "field":
                fname = it[1]
                if fname not in field_numbers:
                    raise KeyError(f"Field '{fname}' not found in <fields>.")
                msg_order_nums.append(field_numbers[fname])
            elif it[0] == "group":
                # include nested group's delimiter (first field num) in parent's message_order
                nested_first = get_first_field_number_of_group_elem(it[2])
                msg_order_nums.append(nested_first)

        # prepare message_order string
        if msg_order_nums:
            msg_order_list = ", ".join(str(n) for n in msg_order_nums) + ", 0"
        else:
            msg_order_list = "0"

        # Add FIELD_SET for the group's count tag at the parent level (indented)
        lines.append(f"{spaces}FIELD_SET(*this, FIX::{name}::{group_name});")
        # Group class header
        lines.append(f"{spaces}class {group_name} : public FIX::Group {{")
        lines.append(f"{spaces}public:")
        lines.append(f"{spaces}    {group_name}() : FIX::Group({group_tag}, {first_field_num}, FIX::message_order({msg_order_list})) {{}}")

        # inside the group class: add FIELD_SET for each field and nested group classes
        for it in items:
            if it[0] == "field":
                fname = it[1]
                lines.append(f"{spaces}    FIELD_SET(*this, FIX::{name}::{fname});")
            elif it[0] == "group":
                # recursively generate nested group class (this will also add the FIELD_SET for the nested group's count tag)
                lines.extend(generate_group_class(it[2], indent + 4))

        lines.append(f"{spaces}}};")
        return lines

    # Generate each message class
    for message in messages.findall("message"):
        msg_name = message.attrib["name"]
        msg_type = message.attrib.get("msgtype", "")

        lines = []
        lines.append("#pragma once")
        lines.append('#include "Message.h"\n')
        lines.append(f"namespace {namespace} {{")
        lines.append(f"class {msg_name} : public Message {{")
        lines.append("public:")
        lines.append(f"    {msg_name}() : Message(MsgType()) {{}}")
        lines.append(f"    {msg_name}(const FIX::Message& m) : Message(m) {{}}")
        lines.append(f"    {msg_name}(const Message& m) : Message(m) {{}}")
        lines.append(f"    {msg_name}(const {msg_name}&) = default;")
        lines.append(f"    {msg_name}({msg_name}&&) = default;")
        lines.append(f"    {msg_name}& operator=(const {msg_name}&) = default;")
        lines.append(f"    {msg_name}& operator=({msg_name}&&) = default;")
        lines.append(f"    static FIX::MsgType MsgType() {{ return FIX::MsgType(\"{msg_type}\"); }}")
        lines.append("")

        # expand message children (fields / groups / components) in order
        items = expand_children(message)

        # top-level fields (after component expansion) — used for generating the convenience constructor
        constructor_fields = [it[1] for it in items if it[0] == "field"]

        # emit FIELD_SET lines and nested group classes in the original order
        for it in items:
            if it[0] == "field":
                fname = it[1]
                lines.append(f"    FIELD_SET(*this, FIX::{name}::{fname});")
            elif it[0] == "group":
                # generate the nested group class (which also emits the FIELD_SET for the group's count tag)
                lines.extend(generate_group_class(it[2], indent=4))

        # convenience constructor for top-level fields (if any)
        if constructor_fields:
            constructor_params = ", ".join([f"const FIX::{name}::{f}& a{f}" for f in constructor_fields])
            lines.append(f"    {msg_name}({constructor_params}) : Message(MsgType()) {{")
            for f in constructor_fields:
                lines.append(f"        set(a{f});")
            lines.append("    }")

        lines.append("};\n")
        lines.append("} // namespace\n")

        output_path = os.path.join(fix_version_path, f"{msg_name}.hpp")
        with open(output_path, "w") as f:
            f.write("\n".join(lines))
        print(f"✅ {msg_name}.hpp generated at: {output_path}")


def generate_messages_h(root: ET.Element, output_dir: str, name: str):
    """Generate a single Messages.h file containing Header, Trailer, and Message classes."""
    fix_version = f"FIX{root.attrib['major']}{root.attrib['minor']}"
    fix_version_lower = f"fix{root.attrib['major']}{root.attrib['minor']}"

    # These sections must exist in the XML
    header_fields = root.find("header")
    trailer_fields = root.find("trailer")
    if header_fields is None:
        raise ValueError("No <header> section found in the XML.")
    if trailer_fields is None:
        raise ValueError("No <trailer> section found in the XML.")

    lines = []
    lines.append("#pragma once")
    lines.append("")
    lines.append("#include <quickfix/Message.h>")
    lines.append("#include <quickfix/Group.h>")
    lines.append("#include \"../FixFields.hpp\"")
    lines.append("")
    lines.append(f"namespace {fix_version}::{name} "+"{")

    # Header class
    lines.append("  class Header : public FIX::Header")
    lines.append("  {")
    lines.append("  public:")
    for field in header_fields.findall("field"):
        field_name = field.attrib["name"]
        lines.append(f"    FIELD_SET(*this, FIX::{name}::{field_name});")

    for group in header_fields.findall("group"):
        group_name = group.attrib["name"]
        group_tag = group.attrib["number"]
        first_field_tag = group[0].attrib["number"] if len(group) > 0 else "0"
        # Create the nested group class
        lines.append(f"    FIELD_SET(*this, FIX::{name}::{group_name});")
        lines.append(f"    class {group_name} : public FIX::Group")
        lines.append("    {")
        lines.append("    public:")
        lines.append(f"      {group_name}() : FIX::Group({group_tag},{first_field_tag},FIX::message_order(" +
                     ",".join([fld.attrib["number"] for fld in group.findall("field")]) + ",0)) {{}}")
        for field in group.findall("field"):
            lines.append(f"      FIELD_SET(*this, FIX::{field.attrib['name']});")
        lines.append("    };")

    lines.append("  };")
    lines.append("")

    # Trailer class
    lines.append("  class Trailer : public FIX::Trailer")
    lines.append("  {")
    lines.append("  public:")
    for field in trailer_fields.findall("field"):
        lines.append(f"    FIELD_SET(*this, FIX::{name}::{field.attrib['name']});")
    lines.append("  };")
    lines.append("")

    lines.append("  class Message : public FIX::Message")
    lines.append("  {")
    lines.append("  public:")
    lines.append("    Message(const FIX::MsgType& msgtype)")
    lines.append(f"    : FIX::Message(FIX::BeginString(\"{fix_version.replace('FIX', 'FIX.')}\") , msgtype) {{}}")
    lines.append("")
    lines.append("    Message(const FIX::Message& m) : FIX::Message(m) {}")
    lines.append("    Message(const Message& m) : FIX::Message(m) {}")
    lines.append("    Header& getHeader() { return (Header&)m_header; }")
    lines.append("    const Header& getHeader() const { return (Header&)m_header; }")
    lines.append("    Trailer& getTrailer() { return (Trailer&)m_trailer; }")
    lines.append("    const Trailer& getTrailer() const { return (Trailer&)m_trailer; }")
    lines.append("  };")
    lines.append("")
    lines.append("}")
    lines.append("")

    namespace_path = os.path.join(output_dir, name)
    fix_version_path = os.path.join(namespace_path, fix_version_lower)
    os.makedirs(fix_version_path, exist_ok=True)

    # Save the file
    output_path = os.path.join(fix_version_path, "Message.h")
    os.makedirs(output_dir, exist_ok=True)
    with open(output_path, "w") as f:
        f.write("\n".join(lines))
    print(f"✅ Messages.h generated at: {output_path}")

def write_field_macros(output_path, name):
    content = """#include <quickfix/Field.h>

#define DEFINE_FIELD_CLASS_NUM( SPACE, NAME, TOK, TYPE, NUM ) \\
namespace SPACE { \\
    class NAME : public TOK##Field { public: \\
        NAME() : TOK##Field(NUM) {} \\
        NAME(const TYPE& value) : TOK##Field(NUM, value) {} \\
};};

#define DEFINE_FIELD_CLASS( SPACE, NAME, TOK, TYPE ) \\
DEFINE_FIELD_CLASS_NUM(SPACE, NAME, TOK, TYPE, FIELD::SPACE::NAME)

#define DEFINE_FIELD_TIMECLASS_NUM( SPACE, NAME, TOK, TYPE, NUM ) \\
namespace SPACE { \\
    class NAME : public TOK##Field { public: \\
        NAME() : TOK##Field(NUM, false) {} \\
        NAME(int precision) : TOK##Field(NUM, precision) {} \\
        NAME(const TYPE& value) : TOK##Field(NUM, value) {} \\
        NAME(const TYPE& value, int precision) : TOK##Field(NUM, value, precision) {} \\
};};

#define DEFINE_FIELD_TIMECLASS( SPACE, NAME, TOK, TYPE ) \\
DEFINE_FIELD_TIMECLASS_NUM(SPACE, NAME, TOK, TYPE, FIELD::SPACE::NAME)

#define DEFINE_CHECKSUM( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, CheckSum, FIX::INT)
#define DEFINE_STRING( SPACE,NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, String, FIX::STRING)
#define DEFINE_CHAR( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, Char, FIX::CHAR)
#define DEFINE_PRICE( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, Price, FIX::PRICE)
#define DEFINE_INT( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, Int, FIX::INT)
#define DEFINE_AMT( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, Amt, FIX::AMT)
#define DEFINE_QTY( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, Qty, FIX::QTY)
#define DEFINE_CURRENCY( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, Currency, FIX::CURRENCY)
#define DEFINE_MULTIPLEVALUESTRING( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, MultipleValueString, FIX::MULTIPLEVALUESTRING)
#define DEFINE_MULTIPLESTRINGVALUE( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, MultipleStringValue, FIX::MULTIPLESTRINGVALUE)
#define DEFINE_MULTIPLECHARVALUE( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, MultipleCharValue, FIX::MULTIPLECHARVALUE)
#define DEFINE_EXCHANGE( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, Exchange, FIX::EXCHANGE)
#define DEFINE_UTCTIMESTAMP( SPACE, NAME ) \\
  DEFINE_FIELD_TIMECLASS(SPACE, NAME, UtcTimeStamp, FIX::UTCTIMESTAMP)
#define DEFINE_BOOLEAN( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, Bool, FIX::BOOLEAN)
#define DEFINE_LOCALMKTDATE( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, String, FIX::LOCALMKTDATE)
#define DEFINE_DATA( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, Data, FIX::DATA)
#define DEFINE_FLOAT( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, Float, FIX::FLOAT)
#define DEFINE_PRICEOFFSET( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, PriceOffset, FIX::PRICEOFFSET)
#define DEFINE_MONTHYEAR( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, MonthYear, FIX::MONTHYEAR)
#define DEFINE_DAYOFMONTH( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, DayOfMonth, FIX::DAYOFMONTH)
#define DEFINE_UTCDATE( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, UtcDate, FIX::UTCDATE)
#define DEFINE_UTCDATEONLY( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, UtcDateOnly, FIX::UTCDATEONLY)
#define DEFINE_UTCTIMEONLY( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, UtcTimeOnly, FIX::UTCTIMEONLY)
#define DEFINE_NUMINGROUP( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, NumInGroup, FIX::NUMINGROUP)
#define DEFINE_SEQNUM( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, SeqNum, FIX::SEQNUM)
#define DEFINE_LENGTH( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, Length, FIX::LENGTH)
#define DEFINE_PERCENTAGE( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, Percentage, FIX::PERCENTAGE)
#define DEFINE_COUNTRY( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, Country, FIX::COUNTRY)
#define DEFINE_TZTIMEONLY( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, String, FIX::TZTIMEONLY)
#define DEFINE_TZTIMESTAMP( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, String, FIX::TZTIMESTAMP)
#define DEFINE_XMLDATA( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, String, FIX::XMLDATA)
#define DEFINE_LANGUAGE( SPACE, NAME ) \\
  DEFINE_FIELD_CLASS(SPACE, NAME, String, FIX::LANGUAGE)
"""
    # Create target directory
    target_dir = os.path.join(output_path, name)
    os.makedirs(target_dir, exist_ok=True)

    # Write file
    file_path = os.path.join(target_dir, "FieldMacros.h")
    with open(file_path, "w") as f:
        f.write(content)
    print(f"✅ FieldMacros.h written to {file_path}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate a FIX MessageCracker header from FIX XML spec.")
    parser.add_argument("--xml", required=True, help="Path to the FIX XML file.")
    parser.add_argument("--name", required=True, help="Namespace name (will be uppercased).")
    parser.add_argument("--output", required=True, help="Root output folder.")

    args = parser.parse_args()
    tree = ET.parse(args.xml)
    root = tree.getroot()

    generate_cracker(root=root, output_dir=args.output, name=args.name)
    generate_fix_fields(root=root, output_dir=args.output, name=args.name)
    generate_field_numbers(root=root, output_dir=args.output, name=args.name)
    generate_fix_values(root=root, output_dir=args.output, name=args.name)
    generate_fix_messages(root=root, output_dir=args.output, name=args.name)
    generate_messages_h(root=root, output_dir=args.output, name=args.name)
    write_field_macros(output_path=args.output, name=args.name)
    