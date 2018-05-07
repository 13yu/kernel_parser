local fs_ffi = require('acid.fs_ffi')

local _M = {}

function _M.read(offset, size)
    local fd, err, errmsg = fs_ffi.open('/dev/fmem')
    if err ~= nil then
       print(string.format('failed to open /dev/fmem: ', err, errmsg))
       return
    end

    local data, err, errmsg = fd:pread(size, offset)
    if err ~= nil then
        print(string.format('failed to read: %s, %s', err, errmsg))
        return
    end

    return data
end

return _M
