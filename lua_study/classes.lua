
Dog = {}

s = 'aaaa' .. 'bbbbb'

function Dog:new()
  newObj = {sound = 'woof'}
  self.__index = self
  return setmetatable(newObj, self)
end
  
function Dog:makeSound()
  print ('I say' .. self.sound)
end

mrDog = Dog:new()
mrDog:makeSound()

LoudDog = Dog:new()

function LoudDog:makeSound()
  s = self.sound .. ' '
  print (s .. s .. s)
end

seymour = Dog:new()
seymour:makeSound()

print '----------'

function printKeys(t)
  for key, val in pairs(t) do 
    print (key, val)
  end
end

print 'Dog keys'
printKeys(Dog)

print 'mrDog keys'
printKeys(mrDog)

print 'LoudDog keys'
printKeys(LoudDog)

print 'seymour'
printKeys(seymour)

print '----------'
