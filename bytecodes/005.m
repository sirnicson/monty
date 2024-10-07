push 5    # 5 onto the stack
push 10   # 10 onto the stack
pall      # Print all (10,5)

push 15   # 15 onto the stack (15, 10, 5)
pop       # Remove top (15)

pint      # Print top (10)

push 20   # 20 onto the stack (20, 10, 5)

add       # Add top two values (20 & 10 = 30 and stores it at the second element 10, replacing it and removing the top element 20)

pall      # Print all (remaining) (30, 5)
