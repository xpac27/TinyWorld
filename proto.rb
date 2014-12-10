COMPONENT_TYPE_A = 0
COMPONENT_TYPE_B = 1

class ComponentA

  @@type = COMPONENT_TYPE_A

  def self.type; @@type; end
  def type;      @@type; end

  attr_accessor :x, :y

  def initialize(x = 0, y = 0)
    @x = x
    @y = y
  end
end

class ComponentB

  @@type = COMPONENT_TYPE_B

  def self.type; @@type; end
  def type;      @@type; end

  attr_accessor :life

  def initialize(life = 100)
    @life = life
  end
end


class World

  def initialize
    @entities = []
    @components = [nil]
    @entity_type_components = []
  end

  def add_entity
    puts "entity ##{@entities.size} created"
    @entities << @entities.size
    @entity_type_components << [0, 0]
    return @entities.size - 1
  end

  def add_entity_component e, c
    puts "component #{c.type} added to entity ##{e}"
    @components << c
    @entity_type_components[e][c.type] = @components.size - 1
    # Add e to the systems using c.type component
  end

  def get_entity_component e, c
    puts "getting comment #{c.type} of entity ##{e}"
    @components[@entity_type_components[e][c.type]]
  end

  def del_entity_component e, c
    puts "component #{c.type} removed from entity ##{e}"
    @entity_type_components[e][c.type] = nil
    @components[@entity_type_components[e][c.type]] = nil
  end

  def del_entity e
    puts "entity ##{e} deleted"
    @components[@entity_type_components[e][0]] = nil
    @components[@entity_type_components[e][1]] = nil
    # Remove e to the systems using c.type component
  end
end



w = World.new

e1 = w.add_entity

w.add_entity_component e1, ComponentA.new(10, 20)
w.add_entity_component e1, ComponentB.new(90)

w.get_entity_component e1, ComponentA
w.get_entity_component e1, ComponentB

w.del_entity_component e1, ComponentA
w.del_entity_component e1, ComponentB

w.del_entity e1


# puts ComponentB.type
# puts ComponentB.new(90).class.type
# puts ComponentB.new(90).type
