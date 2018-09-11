from skimage import io
from skimage.filters.rank import entropy
from skimage.morphology import disk
import cv2

img = cv2.imread("token1.png")
crop=img[200:450, 200:450]
R=25
filtered=entropy(crop, disk(R))
cv2.imshow("token1.png", filtered)
cv2.waitKey(0)
