import tensorflow as tf 
import tflite_runtime.interpreter as tflite
import tensorflow_datasets as tfds 
import numpy as np 
import matplotlib.pyplot as plt 

# 244x 244 사이즈로 리사이즈를 하고, 정규화를 해줍니다. 
def format_image(image,label):
    image = tf.image.grayscale_to_rgb(image)
    image = tf.image.resize(image,(224,224))/255.0
    return image, label

# 훈련, 검증, 테스트 세트로 나눕니다. 
(raw_train, raw_validation, raw_test), metadata =tfds.load(
    'kmnist',  # kmnist 데이터셋으로 변경
    split=['train[:80%]','train[80%:90%]','train[90%:]'],
    with_info=True,
    as_supervised=True,
)

# 테스트 배치 파일을 만들어 줍니다. 
test_batches = raw_test.map(format_image).batch(1)

# 모델 로드 
interpreter = tflite.Interpreter(model_path='f16q_converted_model.tflite')

# 텐서 할당 
interpreter.allocate_tensors()

input_index = interpreter.get_input_details()[0]["index"]
output_index = interpreter.get_output_details()[0]["index"]

predictions =[] 

# 테스트 해보기
# 테스트 배치 파일을 100개 씩 가져와서  
predictions =[] 
test_labels, test_imgs = [],[]
for img, label in test_batches.take(100):
    interpreter.set_tensor(input_index, img)
    interpreter.invoke()
    predictions.append(interpreter.get_tensor(output_index))
    test_labels.append(label.numpy()[0])
    test_imgs.append(img)

# 예측 수 비교 
score  = 0 
for item in range(0,99):
    prediction = np.argmax(predictions[item])
    label = test_labels[item]
    if prediction == label:
        score = score +1

print("100개 중 맞은 예측 수: "+ str(score))

class_names = ['あ', 'い', 'う', 'え', 'お', 'か', 'き', 'く', 'け', 'こ']

def plot_image(i, predictions_array, true_label, img):
    true_label, img = true_label[i], img[i]
    plt.grid(False)
    plt.xticks([])
    plt.yticks([])

    img = tf.squeeze(img)
    plt.imshow(img, cmap=plt.cm.binary)

    predicted_label = np.argmax(predictions_array[i])
    if predicted_label == true_label:
        color = 'blue'
    else:
        color = 'red'

    plt.xlabel("{} {:2.0f}% ({})".format(class_names[predicted_label],
                                          100*np.max(predictions_array[i]),
                                          class_names[true_label]),
                                          color=color)

for index in range(0,100):

    if index%2 == 0 :
      plt.figure(figsize = (6,3))
      plt.subplot(121)
    elif index %2 ==1 :
      plt.subplot(122)

    plot_image(index, predictions, test_labels, test_imgs)
    if index %2 ==1:
      plt.show()
      imgFile = 'resultImg/result{}.png'.format(index)
      plt.savefig(imgFile)
