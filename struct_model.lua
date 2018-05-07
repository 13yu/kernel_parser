local task_struct = require('struct.task_struct')
local atomic_t = require('struct.atomic_t')
local llist_node = require('struct.llist_node')
local sched_entity = require('struct.sched_entity')
local list_head = require('struct.list_head')
local load_weight = require('struct.load_weight')
local rb_node = require('struct.rb_node')
local sched_avg = require('struct.sched_avg')


local _M = {}

_M.task_struct = task_struct.model
_M.atomic_t = atomic_t.model
_M.llist_node = llist_node.model
_M.sched_entity = sched_entity.model
_M.list_head = list_head.model
_M.load_weight = load_weight.model
_M.rb_node = rb_node.model
_M.sched_avg = sched_avg.model


return _M
