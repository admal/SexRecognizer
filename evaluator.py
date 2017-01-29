import tensorflow as tf
import numpy as np


def run(data, path):
    np_input = np.empty([1, 60, 40, 50])
    for x1 in range(60):
        for x2 in range(40):
            for x3 in range(25):
                for x4 in range(2):
                    np_input[0, x1, x2, (x3 * 2) + x4] = data[x3][x1][x2][x4]
    sess = tf.InteractiveSession()
    new_saver = tf.train.import_meta_graph(path + '.meta')
    new_saver.restore(sess, path)
    result = sess.run(tf.get_default_graph().get_tensor_by_name("finalesResult:0"),
                      feed_dict={'DefaultInput:0': np_input, 'DropoutRate:0': 1})
    print(result)
    if result[0][0] > result[0][1]:
        return 0
    else:
        return 1