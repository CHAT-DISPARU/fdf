import os
from PIL import Image

var = "meuf_du_16"

os.makedirs("/home/gajanvie/tronc_commun/cercle_2/fdf/maps/maps_python", exist_ok=True)
img = Image.open("/home/gajanvie/tronc_commun/cercle_2/fdf/maps/img/" + var + ".jpg").convert("RGB")
width, height = img.size

with open("/home/gajanvie/tronc_commun/cercle_2/fdf/maps/maps_python/" + var + ".txt", "w") as f:
    for y in range(height):
        line_entries = []
        for x in range(width):
            r, g, b = img.getpixel((x, y))
            color_hex = f"0x{r:02x}{g:02x}{b:02x}"
            line_entries.append(f"0,{color_hex}")
        f.write(" ".join(line_entries) + "\n")
