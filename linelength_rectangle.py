import cv2
import numpy as np

# https://gist.github.com/tallpeak/ca0f76d0334cc6509aeca113c84905b6?fbclid=IwY2xjawMagk9leHRuA2FlbQIxMABicmlkETE3dTJWd1k4YlBscmlMRlJ0AR4yGs6qBtgwud_dbPBsYNA2ux4dCWhc4ycGHhK1u909NXl6puy9cfglFayBkw_aem_8cWqRr3oLEH0ELG17mFQ4A

# --- 1. Define the physical dimensions of the image ---
# Given physical dimensions: change for your image
IMAGE_WIDTH_IN = 20.39
IMAGE_HEIGHT_IN = 11.47

def calculate_line_length(image_path, physical_width_in, physical_height_in):
    """
    Computes the length of the diagonal line in the image.
    Args:
        image_path (str): Path to the image file.
        physical_width_in (float): The actual physical width of the image in inches.
        physical_height_in (float): The actual physical height of the image in inches.
    Returns:
        float: The computed length of the line in inches.
    """
    try:
        # --- 2. Read and Preprocess the image ---
        img = cv2.imread(image_path)
        if img is None:
            raise FileNotFoundError(f"Could not open or find the image at: {image_path}")

        # Get image dimensions in pixels
        h_px, w_px = img.shape[:2]

        print(f"height {h_px:.2f}, width {w_px:.2f}")

        # Convert to grayscale for simpler processing
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

        # Apply adaptive thresholding to get a binary image of the line
        # The line is black on a white background, so we use THRESH_BINARY_INV
        _, binary = cv2.threshold(gray, 200, 255, cv2.THRESH_BINARY_INV | cv2.THRESH_OTSU)

        # --- 3. Find the contour of the line ---
        # Find contours on the binary image
        contours, _ = cv2.findContours(binary, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        if not contours:
            print("No line contour found.")
            return 0.0

        # The largest contour is likely the line
        line_contour = max(contours, key=cv2.contourArea)

        tot_length = 0
        for i in range(1, len(line_contour)):
            segment_length = np.linalg.norm(line_contour[i] - line_contour[i - 1])
            tot_length += segment_length
            print(f"Segment {i}: Length = {segment_length:.2f}, Total Length = {tot_length:.2f}")

        length_inches = tot_length / np.sqrt(w_px**2 + h_px**2) * np.sqrt(physical_width_in**2 + physical_height_in**2)
        return length_inches

        if False:
            # --- 4. Determine the endpoints from the bounding box ---
            # Get the bounding rectangle (x, y, w, h) of the line
            x, y, w, h = cv2.boundingRect(line_contour)

            # The line runs diagonally from one corner of this bounding box to the other.
            # Endpoints in pixels:
            # For a line from top-left to bottom-right:
            # P1 = (x, y)  (Top-Left)
            # P2 = (x + w, y + h) (Bottom-Right)

            # For a line from top-right to bottom-left:
            # P1 = (x + w, y)  (Top-Right)
            # P2 = (x, y + h) (Bottom-Left)

            # Since the line is straight, the length is the hypotenuse (diagonal) of the bounding box.
            # Length_px = sqrt(w^2 + h^2)
            length_px = np.sqrt(w**2 + h**2)

            # --- 5. Convert pixel length to inches ---

            # Calculate the conversion factors (pixels per inch)
            pixels_per_inch_x = w_px / physical_width_in
            pixels_per_inch_y = h_px / physical_height_in

            # Since the line has both a horizontal and vertical component, we need to convert
            # the pixel dimensions (w and h) to inches first, and then calculate the diagonal length.
            # This accounts for potential non-square pixels if w_px/W != h_px/H, which is common.

            width_in = w / pixels_per_inch_x
            height_in = h / pixels_per_inch_y

            # Calculated Length_in = sqrt(Width_in^2 + Height_in^2)
            length_in = np.sqrt(width_in**2 + height_in**2)

        return length_in

    except Exception as e:
        print(f"An error occurred: {e}")
        return 0.0

# --- Execution ---
# NOTE: Replace with your image.
image_file_path = 'rectangle.jpg'

# Calculate the length
line_length = calculate_line_length(
    image_file_path,
    IMAGE_WIDTH_IN,
    IMAGE_HEIGHT_IN
)

if line_length > 0:
    print(f"The calculated length of the line is: {line_length:.2f} inches")

