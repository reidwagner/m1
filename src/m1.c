#include <Python.h>
#include <stdio.h>
#include <math.h>

inline double hypoth(double theta0, double theta1, double x)
{
    return theta1*x + theta0;  
}

double cost_function(double theta0, double theta1, double *xs, double *ys, size_t m)
{
    double sum = 0;
    size_t i;
    for (i = 0; i < m; i++)
	sum += pow(hypoth(theta0, theta1, xs[i]) - ys[i], 2);
    return sum/(2*m);
}

double *pop_darr(PyObject *iter, size_t *m)
{
    PyObject *item;
    double *darr = malloc(sizeof(double)); //is this best?
    if (!(*darr = PyLong_AsDouble(PyIter_Next(iter)))) {
	fprintf(stderr, "Empty list given.\n");
	exit(1);
    }
    
    *m = 1;
    while ((item = PyIter_Next(iter))) {
	darr = realloc(darr, (*m + 1)*sizeof(double));
	*(darr + *m) = PyLong_AsDouble(item);
	(*m)++;
    }

    return darr;
}

static PyObject* m1_cost_function(PyObject *self, PyObject *args)
{
    PyObject *xs_obj;
    PyObject *ys_obj;
    double theta0;
    double theta1;
    if (!PyArg_ParseTuple(args, "OOdd", &xs_obj, &ys_obj, &theta0, &theta1)) {
	fprintf(stderr, "Failure parsing function arguments.\n");
	exit(1);
    }

    PyObject *xs_iter = PyObject_GetIter(xs_obj);
    PyObject *ys_iter = PyObject_GetIter(ys_obj);
    size_t m = 0;
    double *xs = pop_darr(xs_iter, &m);
    double *ys = pop_darr(ys_iter, &m);

    double cost = cost_function(theta0, theta1, xs, ys, m);
  
    return PyFloat_FromDouble(cost);
  
} 

static PyObject* m1_scratch(PyObject *self, PyObject *args)
{
    return PyLong_FromLong(0);
}

static PyMethodDef m1Methods[] = {
    {"scratch", m1_scratch, METH_VARARGS,
     "For debugging."},
    {"cost_function", m1_cost_function, METH_VARARGS,
     "Calculate the cost function."},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef m1module = {
    PyModuleDef_HEAD_INIT,
    "m1",
    NULL,
    -1,
    m1Methods
};

PyMODINIT_FUNC PyInit_m1(void)
{
    return PyModule_Create(&m1module);
}
