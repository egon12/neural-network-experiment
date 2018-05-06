
typedef struct set_s {
    matrix_t *inputs;
    matrix_t *outputs;
    matrix_t *classes;
    int count;
    double bias;
} set_t

typedef struct data_set_s {
    int input_count;
    int output_count;
    set_t training_set;
    set_t validation_set;
    set_t test_set;
} data_set_t
