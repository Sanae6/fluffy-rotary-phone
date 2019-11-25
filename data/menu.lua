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

function keydown(keycode) --todo later, use numbers as keycodes

end

function stop()
	print("Ended");
end