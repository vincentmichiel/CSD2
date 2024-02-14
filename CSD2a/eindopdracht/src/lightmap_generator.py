# source reference from:
# https://pyimagesearch.com/2016/10/31/detecting-multiple-bright-spots-in-an-image-with-python-and-opencv/

from imutils import contours
from skimage import measure
import numpy as np
import imutils
import cv2
import random 

imageIndex = 0

def generateEvents(beatNumerator):
	global imageIndex
	imageIndex += 1

	if imageIndex > 3:
		imageIndex = 1
	# load the image, convert it to grayscale, and blur it
	image = cv2.imread("/Users/vincent/Documents/CSD2/CSD2a/eindopdracht/src/assets/image"+ str(imageIndex) + ".webp")
	gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
	# apply blur
	blurred = cv2.GaussianBlur(gray, (11, 11), 0)

	# cv2.COLOR_BGR2HSV   <--- convert to HSV for colour identification

	# threshold the image to reveal light regions in the blurred image
	thresh = cv2.threshold(blurred, 200, 255, cv2.THRESH_BINARY)[1]

	# perform a series of erosions and dilations to remove any small blobs of noise from the thresholded image
	thresh = cv2.erode(thresh, None, iterations=2)
	thresh = cv2.dilate(thresh, None, iterations=4)

	# perform a connected component analysis on the thresholded image, then initialize a mask to store only the "large" components
	labels = measure.label(thresh, background=0)
	mask = np.zeros(thresh.shape, dtype="uint8")
	# loop over the unique components
	for label in np.unique(labels):
		# if this is the background label, ignore it
		if label == 0:
			continue
		# otherwise, construct the label mask and count the number of pixels 
		labelMask = np.zeros(thresh.shape, dtype="uint8")
		labelMask[labels == label] = 255
		numPixels = cv2.countNonZero(labelMask)
		# if the number of pixels in the component is sufficiently large, then add it to our mask of "large blobs"
		if numPixels > 300:
			mask = cv2.add(mask, labelMask)
			

	eventData = []

	# find the contours in the mask, then sort them from left to right
	cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
		cv2.CHAIN_APPROX_SIMPLE)
	cnts = imutils.grab_contours(cnts)
	cnts = contours.sort_contours(cnts)[0]
	# loop over the contours
	for (i, c) in enumerate(cnts):
		# draw the bright spot on the image
		(x, y, w, h) = cv2.boundingRect(c)
		((cX, cY), radius) = cv2.minEnclosingCircle(c)
		data = {"x": cX, "y": cY, "r": radius}
		eventData.append(data)
		cv2.circle(image, (int(cX), int(cY)), int(radius),
			(0, 0, 255), 3)
		cv2.putText(image, "#{}".format(i + 1), (x, y - 15),
			cv2.FONT_HERSHEY_SIMPLEX, 0.45, (0, 0, 255), 2)
		
	yLine = 1
	while yLine < beatNumerator:
		cv2.line(image, (int(image.shape[1]/beatNumerator) * yLine, 0), (int(image.shape[1]/beatNumerator) * yLine, image.shape[0]), (0, 255, 0), 3) 
		yLine += 1


	# sort event data
	eventData = sorted(eventData, key=lambda x: x['x'])

	cv2.imshow("Image", image)
	cv2.waitKey(0)
	return image.shape, eventData