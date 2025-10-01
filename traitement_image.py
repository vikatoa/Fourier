from PIL import Image
import numpy as np
import matplotlib.pyplot as plt

def app_kernel(ker, img):
    """
        l'image est en noir et blanc
    """
    img_t = []
    for i in range(len(img) - len(ker)):
        add = []
        for j in range(len(img[i]) - len(ker[0])):
            cum = 0
            for x in range(len(ker)):
                for y in range(len(ker[0])):
                    try:
                        cum += img[i+x][j+y] * ker[x][y]
                    except:
                        print(img[i+x][j+y], ker[x][y], img[i+x][j+y] * ker[x][y], cum)
                        quit()
            add.append(abs(cum))
        img_t.append(add)
    return img_t


image = Image.open('data/capture.jpg')
img = np.array(image)
img_bw = []
for i in img:
    img_bw.append(list(map(lambda x : (float(x[0]) + float(x[1]) + float(x[2]))/3, i)))
img_bw = np.array(img_bw)

kernel1 = [[-1, 0, 1]]
kernel2 = [[-1], [0], [1]]

def mix_images(img1, img2):
    """
        Les deux images sont de même taille
    """
    img_t = []
    for i in range(len(img1)):
        add = []
        for j in range(len(img1[0])):
            add.append((img1[i][j]**2 + img2[i][j]**2)**0.5)
        img_t.append(add)
    return img_t

plt.imshow(mix_images(app_kernel(kernel1, img_bw), app_kernel(kernel2, img_bw)), cmap='gray')
plt.show()
# print(mix_images(app_kernel(kernel1, img_bw), app_kernel(kernel2, img_bw)))
i = Image.fromarray(np.array(mix_images(app_kernel(kernel1, img_bw), app_kernel(kernel2, img_bw))), 'L')
i.save("img.png")