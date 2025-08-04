require "Processor"
require "Aggregator"
require "GeneratorCPP"

def versionXML(type, major, minor, sp)
  dir = "../src"
  xml = "#{type}#{major}#{minor}.xml"
  if (sp != 0)
    xml = "#{type}#{major}#{minor}SP#{sp}.xml"
  end
  return xml
end

def aggregateFields(type, major, minor, sp, aggregator)
  xml = versionXML(type, major, minor, sp)
  Processor.new(xml, [aggregator]).processFields
end

def generateVersion(type, major, minor, sp, verid, aggregator)
  dir = "../codegen/fix"
  xml = versionXML(type, major, minor, sp)
  cpp = GeneratorCPP.new(type, major.to_s, minor.to_s, sp.to_s, verid.to_s, "#{dir}/oe/quickfix")
  processor = Processor.new(xml, [cpp]).process(aggregator)
end

aggregator = Aggregator.new
aggregateFields("FIX", 4, 4, 0, aggregator)
generateVersion("FIX", 4, 4, 0, 0, aggregator)