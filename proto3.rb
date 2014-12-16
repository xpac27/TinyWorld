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
    @components_a_map = []
    @components_b_map = []
  end

  def add_entity mask
    index = @masks.size

    @masks << mask
    @components_a_map << -1
    @components_b_map << -1

    add_entity_component index, mask

    return index
  end

  def has_entity_component entity, mask
    return @masks[entity] & mask > 0
  end

  def get_entity_component entity, mask
    return @components_a[@components_a_map[entity]] if mask == COMPONENT_A
    return @components_b[@components_b_map[entity]] if mask == COMPONENT_B
  end

  def add_entity_component entity, mask
    if mask & COMPONENT_A > 0 
      if @masks[entity] & mask == 0
        @components_a[@components_a_map[entity]] == ComponentA.new 
      else
        @components_a << ComponentA.new 
        @components_a_map[entity] = @components_a.size - 1
      end
    end

    if mask & COMPONENT_B > 0 
      if @masks[entity] & mask == 0
        @components_b[@components_b_map[entity]] == ComponentB.new 
      else
        @components_b << ComponentB.new 
        @components_b_map[entity] = @components_b.size - 1
      end
    end

    @masks[entity] = @masks[entity] | mask
  end

  # def del_entity_component entity, mask
    # @masks[entity] = @masks[entity] ^ mask
  # end

  # def del_entity entity
    # @masks[entity] = COMPONENT_X
  # end
end

w = World.new

e1 = w.add_entity COMPONENT_A
e2 = w.add_entity COMPONENT_A | COMPONENT_B

# w.get_entities COMPONENT_A
# w.get_entities COMPONENT_A | COMPONENT_B

w.get_entity_component e1, COMPONENT_A
w.get_entity_component e2, COMPONENT_A
w.get_entity_component e2, COMPONENT_B

w.add_entity_component e1, COMPONENT_A

w.get_entity_component e1, COMPONENT_A

# w.del_entity_component e1, COMPONENT_A
# w.del_entity_component e1, COMPONENT_B

# w.del_entity e1
