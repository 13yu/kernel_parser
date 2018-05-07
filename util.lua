local struct_model = require('struct_model')


local _M = {}


function _M.get_size(model)
    local total_size = 0

    for _, field in ipairs(model) do
        local field_size = field.size

        if field_size == nil then
            local field_model = struct_model[field.tp]

            if field_model == nil then
                print(string.format('get field size error, no model for: %s', field.tp))
                return
            end

            field_size = _M.get_size(field_model)
        end

        total_size = total_size + field_size
    end

    return total_size
end


function _M.get_field_size(field)
    local field_model = struct_model[field.tp]

    if field_model == nil then
        print(string.format('get field size error, no model for: %s', field.tp))
        return
    end

    local field_size = _M.get_size(field_model)

    return field_size
end


local function char_to_hex(c)
    local hex = string.format('%02X', string.byte(c))
    return hex
end


function _M.to_hex(str)
    local hex_str = string.gsub(str, '.', char_to_hex)
    return hex_str
end


function _M.to_number(str, big_endian)
    local r = 0

    for i = 1, #str do
        local index = i
        if big_endian ~= true then
            index = #str - i + 1
        end

        local c = string.sub(str, index, index)

        r = r * 256 + string.byte(c)
    end

    return r
end


function _M.reverse(str)
    local reversed_str = ''
    for i = 1, #str do
        reversed_str = string.sub(str, i, i) .. reversed_str
    end

    return reversed_str
end


function _M.to_hex_number(str, big_endian)
    if big_endian ~= true then
        str = _M.reverse(str)
    end

    local hex_str = string.gsub(str, '.', char_to_hex)
    return '0x' .. hex_str
end


return _M
