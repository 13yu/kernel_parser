local cjson = require('cjson')
local reader = require('reader')
local parser = require('parser')
local struct_model = require('struct_model')
local util = require('util')


local data = reader.read(0x1883440, 0x100)
print(util.to_hex(data))
--print(struct_model)
--for k, v in ipairs(struct_model.task_struct) do print(k) print (v) end
--print(struct_model.task_struct)
local obj = parser.parse(data, struct_model.task_struct)

print(cjson.encode(obj))
