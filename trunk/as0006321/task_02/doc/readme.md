# ������������ ����������� ���������� ��������

## ���������� �����������

### ���������� ��������������� ����������� �����������

### ������� ���

---

# ������������ ������ �2

## �� ���������� ������� � ������ ��������������� �����������

### ����: ����-�����������

---

**��������:**  
������� 3 �����  
������ ��-63  
���������� �.�.

**��������:**  
������ �. �.

**����� 2024**

---

## ���� ������

�� C++ ����������� ���������, ������������ ���-���������. � �������� ������� ���������� ������������ �������������� ������, ���������� � ���������� ������. ������������ ���, � ��������� ������ ���� �� ����� 3-� ������� (+������������).

## �������

1. �� C++ ����������� ���������, ������������ ������������� ���� ���-���������. � �������� ������� ���������� ������������ �������������� ������, ���������� � ���������� ������. ������������ ���, � ��������� ������ ���� �� ����� 3-� ������� (+������������).
2. �������� ����� �� ����������� ������������ ������ �2 � .md ������� (readme.md) � � ������� pull request ���������� ��� � ��������� ��������: `trunk\as000xxyy\task_02\doc`. � ������ ����� �������� ������� ��� ������ ������� ����������� �������, �������� ���������� ����������.
3. � ����� � ������� Doxygen (� .md �������) �������� ���������� � ������������� ��������� (��������� ������� � �.�.).
4. �������� ��� ���������� ��������� ���������� � ��������: trunk\as000xxyy\task_02\src..

## �������� ���������

��������� ������� �� ��������� �������:

- **Model**: ����������� �����, �������������� ������ �������. �������� ����������� ������� `simulate`, ������� ����� �������������� � �������� �������.
- **LinearModel**: �����, ����������� �������� ������ ���������� ������������. ����� `simulate` ������������ ����� �� ������ �������� ����������� �� ����������� ������ � �������� ������������ �����������.
- **NonlinearModel**: �����, ����������� ���������� ������ ���������� ������������. ����� `simulate` �������� ���������� ��������, ����� ��� ������������ ����������� �� ����������� ������ � �������������� ����������� �� ����������� ������������ �����������.
- **PIDController**: �����, ����������� ���-���������. ����� `compute` ��������� ����������� ����������� �� ������ ��������� �������� � ����������� ��������.
- **Simulation**: �����, ���������� �� ���������� ���������. ����� `run` ��������� ���������, �������� ����� �������� ������ �� ������ ��������� ����.

## ������� ���������� �������

� ���� ������ ���� ��������� ������������ � ���������� ����������� ���-����������. ���� ������������ ������� ���������� ������� ��� ������ ������� ���������� \( Kp, Ki, Kd \).

### ������ 1: Kp = 1.0, Ki = 0.1, Kd = 0.05
![������ 1](path/to/graph1.png)  
**��������**: ��� ����� ���������� ������� ������ ��������� �������� ��������, �� ����������� ��������� ��������� ������ ����.

### ������ 2: Kp = 2.0, Ki = 0.5, Kd = 0.1
![������ 2](path/to/graph2.png)  
**��������**: ���������� ������������ \( Kp \) �������� � ����� ����������� �������, ������ ������� �������� ������ ����������, ��� ��������������� � �����������������.

### ������ 3: Kp = 1.0, Ki = 0.5, Kd = 0.5
![������ 3](path/to/graph3.png)  
**��������**: ���������� ������������� � ����������������� ������������� �������� �������� ��������� � ������� ��������� �������� ��������.

## ��������� ���������� �����������

- **������� � ������� \( Kp \)**: ������������� ������� �� ����������, ��� �������� � ���������� ���������� �������� ��������.
- **������� � �������� \( Kp \)**: ������� �������, �� �������� ��������� � �����������������.
- **����������� �������� \( Ki \) � \( Kd \)**: �������� ��������� ���������� ������ � �������� ���������.

���������� ��������� ���-���������� �������� ���������� ������ ��� ���������� ������ �������.

## ������������

��� ��������� ������������ ������������� Doxygen. � ���������� ��� ������ ���� � ����������� ������� � ��������� ��������� ���������.

### ��������� �������
```plaintext
+-----------------+
|      Model      |
+-----------------+
| + simulate()    |
+-----------------+
          ^
          |
+-----------------+
|  LinearModel    |
+-----------------+
| - a: double     |
| - b: double     |
+-----------------+
| + simulate()    |
+-----------------+
          ^
          |
+-----------------+
|  NonlinearModel |
+-----------------+
| - a: double     |
| - b: double     |
| - c: double     |
| - d: double     |
+-----------------+
| + simulate()    |
+-----------------+
          ^
          |
+-----------------+
|  PIDController   |
+-----------------+
| - Kp: double    |
| - Ki: double    |
| - Kd: double    |
| - prevError: double |
| - integral: double  |
+-----------------+
| + compute()     |
+-----------------+
          ^
          |
+-----------------+
|   Simulation     |
+-----------------+
| - model: Model  |
| - controller: PIDController |
+-----------------+
| + run()         |
+-----------------+