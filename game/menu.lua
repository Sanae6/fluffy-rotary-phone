function begin()
	loadTexture("data/clownpiece.png","clown");
	print("Start");
end

function draw()
	--print("Draw");
	drawTexture("clown")
end

function update()
	--print("Update")
end
W = 119
A = 97
S = 115
D = 100
function keydown(keycode) --todo later, use numbers as keycodes
	print(keycode)
	if (keycode == W)
end

function keyup(keycode)

end

function closing()--runs after render when game is set to close, meant to catch that for any reason
	
end

function stopped()--ran right before sdl closes
	print("Ended");
end