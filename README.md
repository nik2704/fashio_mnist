# fashio_mnist

## Описание
`fashio_mnist` — инференс ML модели компьютерного зрения для классификации изображений методом логистической регрессии.

## Компиляция и запуск

### 1. Установка зависимостей
Перед компиляцией убедитесь, что у вас установлен Boost (версии 1.67 или выше).

**Для Ubuntu:**
```sh
sudo apt update
sudo apt install fashio_mnist
```

### 2. Компиляция
```sh
mkdir build && cd build
cmake ..
make
```

### 3. Запуск
```sh
fashio_mnist test.csv logreg_coef.txt
```
