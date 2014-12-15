COMPONENT_X = 0
COMPONENT_A = 1 << 0
COMPONENT_B = 1 << 1

class ComponentA

  attr_accessor :x, :y

  def initialize(x = 0, y = 0)
    @x = x
    @y = y
  end
end

class ComponentB

  attr_accessor :life

  def initialize(life = 100)
    @life = life
  end
end

class World

  def initialize
    @masks = [];
    @components_a = []
    @components_b = []
  end

  def add_entity mask
    @masks << mask
    @components_a << ComponentA.new
    @components_b << ComponentB.new
    @masks.size - 1
  end

  def add_entity_component entity, component
    @components_a[entity] = ComponentA.new if component == COMPONENT_A
    @components_b[entity] = ComponentB.new if component == COMPONENT_B
    @masks[entity] = @masks[entity] | component
  end

  def has_entity_component entity, component
    @masks[entity] & component > 0
  end

  def get_entity_component entity, component
    return @components_a[entity] if component == COMPONENT_A
    return @components_b[entity] if component == COMPONENT_B
  end

  def del_entity_component entity, component
    @masks[entity] = @masks[entity] ^ component
  end

  def del_entity entity
    @masks[entity] = COMPONENT_X
  end
end

w = World.new

e1 = w.add_entity COMPONENT_A | COMPONENT_B

w.get_entity_component e1, COMPONENT_A
w.get_entity_component e1, COMPONENT_B

w.del_entity_component e1, COMPONENT_A
w.del_entity_component e1, COMPONENT_B

w.del_entity e1
