local struct_model = require('struct_model')
local util = require('util')

local _M = {}


function _M.parse_number(bytes)
    local bytes = util.reverse(bytes)
    return {
        hex = util.to_hex(bytes),
        --bin = util.to_bin(bytes),
        value = util.to_number(bytes, true),
    }
end


local base_parsers = {
    number = _M.parse_number,
}


function _M.parse_one_field(bytes, field)
    local base_parser = base_parsers[field.tp]
    if base_parser ~= nil then
        return base_parser(bytes)
    end

    if field.pointer == true then
        return {}
    end

    local field_model = struct_model[field.tp]
    if field_model == nil then
        print(string.format('no mode for type: %s, of field: %s',
                            field.tp, field.name))
        return
    end

    return _M.parse(bytes, field_model)
end


function _M.parse(bytes, model)
    local obj = {}
    local index = 1

    for _, field in ipairs(model) do
        if field.size == nil then
            field.size = util.get_field_size(field)
        end
        local sub_bytes = string.sub(bytes, index, index + field.size - 1)
        index = index + field.size

        obj[field.name] = _M.parse_one_field(sub_bytes, field)
    end

    return obj
end


return _M
