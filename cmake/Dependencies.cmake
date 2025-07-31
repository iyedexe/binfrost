file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/oe)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/md)

file(DOWNLOAD 
    https://raw.githubusercontent.com/binance/binance-spot-api-docs/master/fix/schemas/spot-fix-oe.xml 
    ${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/oe/broker.xml
)

file(DOWNLOAD 
    https://raw.githubusercontent.com/binance/binance-spot-api-docs/master/fix/schemas/spot-fix-md.xml 
    ${CMAKE_CURRENT_SOURCE_DIR}/codegen/fix/md/feeder.xml
)