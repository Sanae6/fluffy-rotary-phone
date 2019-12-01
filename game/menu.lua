player = {x=0.0,y=0.0}
W = 119
A = 97
S = 115
D = 100
keys = {W=false,A=false,S=false,D=false}
function begin()
	loadTexture("data/clownpiece.png","clown");
	print("Start");
end

function draw()
	--print("Draw");
	drawTexture("clown",player.x, player.y)
end

function update(time,delta)
	if keys.W then player.y = player.y - delta end
	if keys.S then player.y = player.y + delta end
	if keys.A then player.x = player.x - delta end
	if keys.D then player.x = player.x + delta end
end
function keydown(keycode) --todo later, use numbers as keycodes
	if keycode == W then keys.W = true end
	if keycode == S then keys.S = true end
	if keycode == A then keys.A = true end
	if keycode == D then keys.D = true end
end

function keyup(keycode)
	if keycode == W then keys.W = false end
	if keycode == S then keys.S = false end
	if keycode == A then keys.A = false end
	if keycode == D then keys.D = false end
end

function closing()--runs after render when game is set to close, meant to catch that for any reason
	
end

function stopped()--ran right before sdl closes
	print("Ended")
end