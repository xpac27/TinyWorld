module Entity

  @@entities = []

  def self.create
    id = @@entities.size
    @@entities << id
    puts '- Created entity #' << id.to_s
    return id
  end

  def self.destroy id
    puts '- Destroyed entity #' << id.to_s
  end

  def self.add_component(id, component)
    puts '- Add component ' << component.name << ' to entity #' << id.to_s
  end

  def self.del_component(id, component)
    puts '- Delete component ' << component.name << ' from entity #' << id.to_s
  end

  def self.bind_system_to_component system, components
  end
end

class SystemA

  Entity.bind_system_to_component self, [ComponentA]
end

class SystemB

  Entity.bind_system_to_component self, [ComponentA, ComponentB]
end

class Component

  def name
    'Unnamed component'
  end
end

class ComponentA < Component

  def name
    'A'
  end
end

class ComponentB < Component

  def name
    'B'
  end
end

e1 = Entity.create
Entity.add_component(e1, ComponentA.new)
Entity.add_component(e1, ComponentB.new)

