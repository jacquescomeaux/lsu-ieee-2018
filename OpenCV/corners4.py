import cv2
import numpy as np
import os

lowerBound = np.array([0,0,0])
upperBound = np.array([179,255,180])

threshold_area_low = 6000
threshold_area_high = 16000

#cam = cv2.VideoCapture(1)
kernelOpen = np.ones((10,10))
kernelClose = np.ones((50,50))

folder = 'board_pictures/'
files=os.listdir(folder)

for file in files:

    img = cv2.imread(folder + file)
    imgHSV = cv2.cvtColor( img, cv2.COLOR_BGR2HSV )
    #thresh,binary=cv2.threshold(imgHSV, 170, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)
    mask = cv2.inRange( imgHSV, lowerBound, upperBound)  

    maskOpen = cv2.morphologyEx( mask, cv2.MORPH_OPEN, kernelOpen )

    maskClose = cv2.morphologyEx( maskOpen, cv2.MORPH_CLOSE, kernelClose )

    maskFinal=maskClose

    _,conts,h = cv2.findContours( maskFinal.copy(), cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE )
    
    print(conts)
    for cont in conts:
        area = cv2.contourArea(cont)
        if (area > threshold_area_low) and (area < threshold_area_high):
            x,y,w,h = cv2.boundingRect(cont)
            if (w < 300) and (h < 300):
                
                #create new blank black image of same size to impose contour
                height, width = img.shape[:2]
                cont_img = np.zeros((height,width,3), np.uint8)
                
                #create polyline from contour
                epsilon = .015*cv2.arcLength(cont,True)
                approx = cv2.approxPolyDP(cont,epsilon,True)
                
                #draw polyline onto black image
                cv2.drawContours(cont_img, [approx], -1, (255,0,0), 3)
                #cv2.drawContours(img, cont, -1, (255,0,0), 3)
                
                #fill contour to be white
                cv2.fillConvexPoly(cont_img, approx, (255,255,255))
                
                #convert to grayscale
                cont_img = cv2.cvtColor(cont_img,cv2.COLOR_BGR2GRAY)
                
                #find canny edges
                edge_img = cv2.Canny(cont_img,100,200,apertureSize = 3)
                
                #convert image to float32 numpy array
                edge_np = np.float32(edge_img)
                
                #detect corner locations
                dst = cv2.cornerHarris(edge_np,15,15,0.04)

                #dilate result
                dst = cv2.dilate(dst,None,iterations=3)
                
                # non-maximum suppression via dilation
                kernel = np.ones((50,50))
                max_dst = cv2.dilate(dst, kernel, iterations=1)   
                dst = dst * (dst == max_dst)
                
                sub = False
                
                if sub:
                    ret, dst = cv2.threshold(dst,0.02*dst.max(),255,0)
                    dst = np.uint8(dst)
                    
                    # find centroids
                    ret, labels, stats, centroids = cv2.connectedComponentsWithStats(dst)
                    
                    # define the criteria to stop and refine the corners
                    criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 100, 0.001)
                    corners = cv2.cornerSubPix(edge_np,np.float32(centroids),(5,5),(-1,-1),criteria)
                                    
                    # Now draw them
                    res = np.hstack((centroids,corners))
                    res = np.int0(res)
                    #img[res[:,1],res[:,0]]=[0,0,255]
                    img[res[:,3],res[:,2]] = [0,255,0]
                    
                else:
                    #draw corners
                    img[dst>.025*dst.max()] = [0,0,255]

    cv2.imshow('gray', cont_img)
    cv2.imshow('edges', edge_img)
    cv2.imshow('corners', img)
    
    k = cv2.waitKey(0)
    if k%256 == 27:
        # ESC pressed
        print("Escape hit, closing...")
        break
    

		#if xtemp > 22:
		#	break

#cam.release()
cv2.destroyAllWindows()



