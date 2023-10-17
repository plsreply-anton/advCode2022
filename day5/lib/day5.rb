def readFile(filename)
    actions = Array.new

    containers = Array.new(9) { Array.new }

    file = File.open(filename, "r")
    file.each_line do |line|
        matches = line.scan(/\[(.*?)\]/)
        i0 = 0
        iter = 0
        matches.each_with_index do |match, index|
            i = matches.count(match)

            if i > 0
                line.index(match[0], iter)
                containers[((line.index(match[0], iter)))/4].push(match[0])
                iter = 1 + line.index(match[0], iter)
            else
                containers[((line.index(match[0])))/4].push(match[0])
            end
        end

        if line.include? "move"
            actions.push(line)
        end

    end
    file.close
    return containers, actions
end


def makeActionArrays(actionArray)

    # Initialize arrays
    move_array = Array.new
    from_array = Array.new
    to_array = Array.new

    actionArray.each do |string|
        # Use regular expressions to find and extract integers
        integers = string.scan(/\d+/).map(&:to_i)

        # Depending on the number of integers found, populate the arrays
        case integers.length
        when 3
            move_array.push(integers[0])
            from_array.push(integers[1])
            to_array.push(integers[2])
        else
            puts "Invalid input: #{input_string}"
        end
    end
    return move_array, from_array, to_array
end

def moveAround(containers, move_array, from_array, to_array)
    for i in 0...move_array.length do
        items_to_move = move_array[i]
        from_container = from_array[i] - 1
        to_container = to_array[i] - 1

        moved_items = containers[from_container].shift(items_to_move)

        if moved_items.is_a?(Array)
          moved_items.each do |item|
            containers[to_container].unshift(item)
          end
        else
          containers[to_container].unshift(moved_items)
        end
      end

    return containers
end



# containers, actions = readFile("day5Input.txt")
# move_array, from_array, to_array = makeActionArrays(actions)
# containers = moveAround(containers, move_array, from_array, to_array)

# containers.each do |column|
#     puts column[0]
#     puts " "
# end


####### Part 2
def moveAroundPart2(containers, move_array, from_array, to_array)
    for i in 0...move_array.length do
        items_to_move = move_array[i]
        from_container = from_array[i] - 1
        to_container = to_array[i] - 1

        moved_items = containers[from_container].shift(items_to_move)
        # puts moved_items
        # puts " "

        if moved_items.is_a?(Array)
            moved_items.reverse().each do |item|
                containers[to_container].unshift(item)
        end
        else
            containers[to_container].unshift(moved_items)
      end

        # if i == 2
        #     break
        # end
      end
    return containers
end

containers2, actions = readFile("day5Input.txt")
move_array, from_array, to_array = makeActionArrays(actions)
containers2 = moveAroundPart2(containers2, move_array, from_array, to_array)

containers2.each do |column|
    puts column[0]
    puts " "
end
