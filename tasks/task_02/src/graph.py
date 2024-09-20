import matplotlib.pyplot as plt

# Данные
time = [1, 2, 3, 4, 5]
linear_model = [2, 3, 4, 5, 6]
nonlinear_model = [2.84147, 3.68294, -2.54954, -14.2721, -18.9308]
error = [-0.841471, -0.682942, 6.54954, 19.2721, 24.9308]
control_signal = [-2.52441, -2.04883, 18.8072, 56.292, 79.8177]

# Построение графика
plt.plot(time, linear_model, label='Linear Model', color='blue')
plt.plot(time, nonlinear_model, label='Nonlinear Model', color='red')
plt.plot(time, error, label='Error', color='green')
plt.plot(time, control_signal, label='Control Signal', color='black')

# Настройка графика
plt.xlabel('Time')
plt.ylabel('Values')
plt.title('Graph of Models and Control Signal')
plt.legend()
plt.grid(True)

# Показать график
plt.show()
