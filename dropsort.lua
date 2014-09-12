function main()
local function avg(a)
    local sum, length = 0, #a
    for i = 1, length do sum = sum + a[i] / length end
    return sum
end

local function print_arr(a)
    if #a > 0 then
        for i = 1, #a do print(i, a[i]) end
    else
        print("[empty]")
    end
end

local function rand_arr(length, range)
    range = range or 100
    local a = {}
    for i = 1, length do a[i] = range * math.random() end
    return a
end

local tput, tdel = table.insert, table.remove

local function extend_arr(a, b)
    for i = 1, #b do tput(a, b[i]) end
    return a
end

local function merge(a, b)
    if DEBUG then
        print("merge a:")
        print_arr(a)
        print("merge b:")
        print_arr(b)
    end
    
    r = {}
    while #a > 0 and #b > 0 do
        if a[1] < b[1] then
            tput(r, tdel(a, 1))
        else
            tput(r, tdel(b, 1))
        end
    end
    if #a > 0 then
        r = extend_arr(r, a)
    else
        r = extend_arr(r, b)
    end
    return r
end

local function dropsort(a)
    local n = #a
    if n < 2 then return a end
    
    local down = {}
    
    local i = 2
    while i <= n do
        if a[i] >= a[i - 1] then
            i = i + 1
        else
            tput(down, tdel(a, i))
            n = n - 1
        end
    end
    
    if DEBUG then
        print("a:")
        print_arr(a)
        print("down:")
        print_arr(down)
    end
    
    return merge(a, dropsort(down))
end

math.randomseed(29834)
local test = rand_arr(100)

print("\nUnsorted:")
print_arr(test)

test = dropsort(test)

print("\nSorted:")
print_arr(test)
end -- main
main()