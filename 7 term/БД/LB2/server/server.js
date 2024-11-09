const express = require('express');
const { Pool } = require('pg');

const app = express();
const port = 3001;

const pool = new Pool({
  user: 'postgres',
  host: 'localhost',
  database: 'semestr7',
  password: '11111',
  port: 5433,
});

app.use(express.json());

app.get('/', (req, res) => {
  res.send('Сервер работает успешно');
});

const getTableData = async (req, res, table) => {
  try {
    const client = await pool.connect();
    const result = await client.query(`SELECT * FROM ${table}`);
    const data = result.rows;
    res.json(data);
    client.release();
  } catch (err) {
    console.error(err);
    res.status(500).send('Internal server error');
  }
};

app.get('/client', async (req, res) => {
  await getTableData(req, res, 'client');
});

app.get('/disks', async (req, res) => {
  await getTableData(req, res, 'disk');
});

app.get('/film', async (req, res) => {
  await getTableData(req, res, 'film');
});

app.get('/orders', async (req, res) => {
  await getTableData(req, res, '"order"');
});

app.get('/query', async (req, res) => {
  const { query } = req.query;
  try {
    const result = await pool.query(query);
    res.json(result.rows);
  } catch (err) {
    console.error(err);
    res.status(500).send('Internal server error');
  }
});

app.listen(port, () => {
  console.log(`Server is running at http://localhost:${port}`);
});