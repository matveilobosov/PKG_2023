import tkinter as tk
from tkinter import filedialog
from copy import deepcopy

import cv2
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image, ImageTk


class ImageProcessor:

    def __init__(self) -> None:

        self.root = tk.Tk()
        self.root.title("Image processor")

        self.default_image = np.zeros((300, 300, 3), dtype=np.uint8)
        self.default_image[:] = (255, 255, 255)

        self.image = None
        self.processed_image = None
        self.panel = tk.Label(self.root)
        self.panel.pack(side="left", padx=10, pady=7)

        self._setup_buttons()


    def _setup_buttons(self) -> None:

        self.open_btn = tk.Button(
            self.root, text="Open Image", command=self.open_image
        )
        self.open_btn.pack(pady=7)

        self.original_btn = tk.Button(
            self.root, text="Show Original", command=self.show_original_image
        )
        self.original_btn.pack(pady=7)

        self.points_btn = tk.Button(
            self.root, text="Show Points", command=self.show_points
        )
        self.points_btn.pack(pady=7)

        self.gradient_btn = tk.Button(
            self.root, text="Show Gradient Magnitude", command=self.show_gradient_magnitude
        )
        self.gradient_btn.pack(pady=7)

        self.edges_btn = tk.Button(
            self.root, text="Show Edges", command=self.show_edges
        )
        self.edges_btn.pack(pady=7)

        self.global_threshold_btn = tk.Button(
            self.root, text="Global Threshold", command=self.show_global_threshold
        )
        self.global_threshold_btn.pack(pady=7)

        self.adaptive_threshold_btn = tk.Button(
            self.root, text="Adaptive Threshold", command=self.show_adaptive_threshold
        )
        self.adaptive_threshold_btn.pack(pady=7)




    def resize_image(self, image, width=None, height=None):
        h, w = image.shape[:2]

        if width is None and height is None:
            return image

        if width is None:
            aspect_ratio = height / h
            new_width = int(w * aspect_ratio)
            new_size = (new_width, height)
        else:
            aspect_ratio = width / w
            new_height = int(h * aspect_ratio)
            new_size = (width, new_height)

        resized_img = cv2.resize(image, new_size, interpolation=cv2.INTER_AREA)
        return resized_img


    def open_image(self):
        file_path = filedialog.askopenfilename()

        if file_path:
            self.image = cv2.imread(file_path)
            self.processed_image = np.copy(self.image)
            self.display_image(self.processed_image)
        else:
            self.image = None
            self.processed_image = None
            self.display_image(self.default_image)


    def show_original_image(self):
        if self.image is None:
            return
        self.processed_image = np.copy(self.image)
        self.display_image(self.processed_image)


    def show_points(self):
        if self.image is None:
            return

        gray = cv2.cvtColor(self.image, cv2.COLOR_BGR2GRAY)
        edges = cv2.Canny(gray, threshold1=50, threshold2=150, apertureSize=3)

        sobelx = cv2.Sobel(gray, cv2.CV_64F, 1, 0, ksize=5)
        sobely = cv2.Sobel(gray, cv2.CV_64F, 0, 1, ksize=5)

        gradient_magnitude = cv2.magnitude(sobelx, sobely)
        gradient_magnitude = cv2.normalize(gradient_magnitude, None, 0, 255, cv2.NORM_MINMAX).astype(np.uint8)

        all_points = cv2.bitwise_or(edges, gradient_magnitude)
        self.display_image(all_points)


    def show_gradient_magnitude(self):
        if self.image is None:
            return

        gray = cv2.cvtColor(self.image, cv2.COLOR_BGR2GRAY)

        sobelx = cv2.Sobel(gray, cv2.CV_64F, 1, 0, ksize=5)
        sobely = cv2.Sobel(gray, cv2.CV_64F, 0, 1, ksize=5)

        gradient_magnitude = cv2.magnitude(sobelx, sobely)
        gradient_magnitude = cv2.normalize(gradient_magnitude, None, 0, 255, cv2.NORM_MINMAX).astype(np.uint8)
        self.display_image(gradient_magnitude)


    def show_edges(self):
        if self.image is None:
            return
        gray = cv2.cvtColor(self.image, cv2.COLOR_BGR2GRAY)
        edges = cv2.Canny(gray, threshold1=50, threshold2=150, apertureSize=3)
        self.display_image(edges)


    def display_image(self, img):
        img = self.resize_image(img, width=650, height=650)
        img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        img = Image.fromarray(img)
        img = ImageTk.PhotoImage(image=img)
        self.panel.config(image=img)
        self.panel.image = img

    def run(self) -> None:
        self.display_image(self.default_image)
        self.root.mainloop()


    def show_global_threshold(self):
        if self.image is None:
            return

        gray = cv2.cvtColor(self.image, cv2.COLOR_BGR2GRAY)
        ret, thresh1 = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY_INV | cv2.THRESH_OTSU)
        self.processed_image = thresh1
        self.display_image(self.processed_image)

    def show_adaptive_threshold(self):
        if self.image is None:
            return

        gray = cv2.cvtColor(self.image, cv2.COLOR_BGR2GRAY)
        thresh2 = cv2.adaptiveThreshold(gray, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C, cv2.THRESH_BINARY, 11, 2)
        self.processed_image = thresh2
        self.display_image(self.processed_image)
        


def main() -> None:
    processor = ImageProcessor()
    processor.run()
 

if __name__ == "__main__":
    main()
