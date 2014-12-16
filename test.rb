class Test

  def initialize size
    @pad_left = 8
    @pad_right = 8
    @components = []
    @map = []
    size.times {|i| 
      @map << nil 
      @components << nil
    }
  end

  def new_component
    Random.rand(99999999)
  end

  def add_entity_component entity
    add_entity_component_0 entity
  end

  def add_entity_component_0 entity
    if @components.size > entity

      if @components[entity].nil?
        @map[entity] = entity
        @components[entity] = new_component
      else

        # look left
        left = entity and (entity - 1).downto(0) { |i| left = i and break if @components[i].nil? }
        # look right
        right = entity and (entity + 1).upto(@components.size - 1) { |i| right = i and break if @components[i].nil? }

        if entity - left > right - entity
          # right closer
          @map[entity] = right
          @components[right] = new_component
        else
          # left closer
          @map[entity] = left
          @components[left] = new_component
        end
      end
    else
      @map[entity] = (@components << new_component).size - 1
    end
  end

  def del_entity_component entity
    return if @map[entity].nil?
    @components[@map[entity]] = nil
    @map[entity] = nil
  end

  def total_components
    @components.size
  end

  def differences
    # count differences between map value (component index) and map index
    @map.each.with_index.reduce(0) {|sum,(value,index)| 
      value.nil? || value == index ? sum : sum + 1
    }
  end

  def discontinuities
    # count accurences of degreasing index values
    current = 0
    @map.find_all {|i| !i.nil? }.reduce(0) {|sum, value| 
        sum += 1 if value < current
        current = value 
        sum
    }
  end

  def memory_fetches
    # count how many time main ram would be fetched
    position = 0
    @map.find_all {|i| !i.nil? }.reduce(1) {|sum, value| 
      if position - @pad_left <= value && value <= position + @pad_right
        sum
      else
        position = value
        sum = sum + 1
      end
    }
  end
end

test = Test.new(100)

data_total_components = []
data_differences = []
data_discontinuities = []
data_memory_fetches = []

500.times do
  test.del_entity_component Random.rand(100)
  test.add_entity_component Random.rand(100)
  data_total_components << test.total_components
  data_discontinuities << test.discontinuities
  data_differences << test.differences
  data_memory_fetches << test.memory_fetches
end

def array_ceil array, ceil
  max = array.max.to_f
  array.map {|value| (value / max) * ceil }
end

require 'gruff'
g = Gruff::Line.new
g.theme = Gruff::Themes::GREYSCALE
g.hide_dots = true
g.font = 'myriadwebpro-bold.ttf'
g.data :Components, data_total_components, '#000000'
g.data :Discontinuities, data_discontinuities, '#00ff00'
g.data :Differences, data_differences, '#0000ff'
g.data :Fetches, data_memory_fetches, '#ff0000'
g.write('test.png')
