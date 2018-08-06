import numpy as np

# STEP 1

def hadamard(m1, m2):
    """ m1 and m2 is matrix """
    return m1.A * m2.A


# STEP 2
def output_to_class(result_array):
    if is_same_array(result_array, [1,0,0]):
        return 1

    if is_same_array(result_array, [0,1,0]):
        return 2

    if is_same_array(result_array, [0,0,1]):
        return 3

    return 0

def is_same_array(result_array, condition_list):
    new_a = np.array(condition_list)
    condition = (result_array == new_a) == False
    return np.where(condition)[0].size == 0

# STEP 3


class DataChildSet:
    def __init__(self, ar):
        self.inputs = np.float32(ar[:,0:4])
        self.outputs = np.intp(ar[:,4:7])
        self.classes = np.array(list(map(lambda x: output_to_class(x), self.outputs)))
        self.count = self.outputs.size
        self.bias = np.array([])

        self.inputs_m = np.matrix(self.inputs)
        self.outputs_m = np.matrix(self.outputs)



class DataSet:
    def __init__(self, training_file, validation_file, test_file):
        self.training_set = DataChildSet(self.load_dataset(training_file))
        self.validation_set = DataChildSet(self.load_dataset(validation_file))
        self.test_set = DataChildSet(self.load_dataset(test_file))
        self.input_count = self.training_set.inputs.size + self.validation_set.inputs.size + self.test_set.inputs.size
        self.output_count = self.training_set.outputs.size + self.validation_set.outputs.size + self.test_set.outputs.size


    def load_dataset(self, filename):
        f = open(filename, "r")
        s = f.read()
        f.close()
        l = map(lambda it: it.split("\t"), s.splitlines())
        return np.array(list(l))




# STEP 4
def activation(x):
    return (np.tanh(x) + 1)/2

def activation_d(x):
    return (1 - np.tanh(x)**2) / 2

# STEP 5

def feed_forward(inputs, weight, bias):
    #net = weight * np.concatenate((inputs, bias), axis=1)
    net = np.concatenate((inputs, bias), axis=1) * weight
    output = activation(net)
    return (output, net)


# STEP 6
def init_weight(width, height, max_weight):
    return np.matrix((np.random.rand(height, width) * max_weight * 2) - max_weight)


# STEP 7
def evaluate_network(inputs, weight, target_output, target_class, bias):
    outputs, net = feed_forward(inputs, weight, bias)
    diff = target_output - outputs
    diff_square = (diff.A * diff.A)
    error = np.sum(diff_square) / (3 * len(outputs))

    classes = output_to_class(outputs)
    class_error = np.sum(classes != target_class) / len(outputs)
    return(error, class_error)


# STEP 8
def back_propagation(inputs, target_outputs, weight, learning_rate, bias):
    return weight


# STEP 9
def train(training_set, validation_set, test_set):
    weight = init_weight(1,5,0.5)
    training_set.bias = np.ones((len(training_set.inputs), 1))
    validation_set.bias = np.ones((len(validation_set.inputs), 1))
    test_set.bias = np.ones((len(test_set.inputs), 1))

    i = 0
    while (i < 500):
        i += 1
        back_propagation(training_set.inputs_m, weight, 0.1, training_set.bias)
        error, class_error = evaluate_network(training_set.inputs_m, weight, training_set.outputs_m, training_set.classes, training_set.bias)
        print(error, class_error)

    return (weight, error)

# STEP 10

data_set = DataSet("iris_data_files/iris_training.dat", "iris_data_files/iris_validation.dat", "iris_data_files/iris_test.dat")

# STEP 11

train(data_set.training_set, data_set.validation_set, data_set.test_set)


# STEP 12

def back_propagation(inputs, target_outputs, weight, learning_rate, bias):

    outputs, net = feed_forward(inputs, weight, bias)
    error_vector = target_ouputs - outputs
    delta = hadamard(error_vector)

    return weight

