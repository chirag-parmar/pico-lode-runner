import numpy as np
from PIL import Image

def convert_sprite(k, l, n, a):
	print("static const uint16_t sprite_" + str(n) + "[] = {")
	for i in range(k, k + 16):
		inner_array = []
		print("\t", end="")
		for j in range(l, l + 16):
			hexcode = '0x{:04x}'.format((((a[i][j][0] >> 3) & 0x1F) << 11) | (((a[i][j][1] >> 2) & 0x3F) << 5) | ((a[i][j][2] >> 3) & 0x1F))
			print(hexcode, end=", ")
		print("")

	print("};\n")

def extract_sprites(path):

	img= Image.open(path)
	arr = np.array(img)

	num_sprites_x = arr.shape[0] // 16
	num_sprites_y = arr.shape[1] // 16

	# raise Exception("hello")

	for k in range(num_sprites_x):
		for l in range(num_sprites_y):
			convert_sprite(k, l, k*num_sprites_y + l, arr)

extract_sprites('/Users/chirag/Desktop/EMBEDDED/lode-runner-pico/src/sprites/lode-runner-char-tiles.png',)