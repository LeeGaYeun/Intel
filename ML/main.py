import numpy as np
from PIL import Image
import matplotlib.pyplot as plt

color_img = Image.open('fruits.jpg')
plt.imshow(color_img)
plt.show()