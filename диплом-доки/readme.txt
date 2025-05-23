============================
Запуск проекта - веб-платформа для работы с моделями нейронных сетей
============================

1. Установите зависимости

Серверная часть (Node.js + Python):
---------------------------
# Перейдите в директорию server
cd server

# Установите зависимости Node.js
npm install

# Установите зависимости Python
cd ../server-models
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt


Клиентская часть (React):
-----------------
# Перейдите в директорию client
cd ../client

# Установите зависимости
npm install

cd ../

2. Настройка базы данных (PostgreSQL)
-------------------------------------
# Создайте базу данных вручную, если ещё не создана
createdb neuro_lab

# Выполните дамп, чтобы восстановить структуру и данные
psql -U <ваш_пользователь> -d neuro_lab -f db/db_dump.sql


3. Запуск проекта
-----------------

Серверная часть:
--------
# Запуск Node.js-сервера
cd backend
node ./server/app.js

# Запуск Python-сервера (FastAPI)
# В отдельном терминале
cd server-models
source venv/bin/activate
uvicorn models:app --host 0.0.0.0 --port 8001 --reload


Клиентская часть:
cd ../client
npm run dev

Платформа будет доступна по адресу:
http://localhost:3000