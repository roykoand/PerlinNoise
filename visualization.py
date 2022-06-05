import argparse
from tkinter.messagebox import NO

import matplotlib.pyplot as plt
import numpy as np

import perlin


def perlin2d_example(lin_a: int = 0, lin_b: int = 10, n_samples: int = 600, cmap: str="YlGnBu") -> None:
    print(cmap)
    lin = np.linspace(lin_a, lin_b, n_samples)
    x, y = np.meshgrid(lin, lin)
    img = np.zeros(x.shape)

    for i in range(img.shape[0]):
        for j in range(img.shape[1]):
            img[i][j] = perlin.perlin2d(x[i][j], y[i][j])
    plt.title(f"Color map = {cmap}")
    plt.imshow(img, cmap=cmap)
    plt.colorbar()
    plt.savefig(f"perling2d_{cmap}.png")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-perlin2d", action="store_true", help="Example image for Perlin 2d algorithm"
    )
    parser.add_argument(
        "-cmap", help="Here you can specify the matplotlib color map"
    )
    args = parser.parse_args()
    
    if args.perlin2d:
        perlin2d_example(cmap=args.cmap)
