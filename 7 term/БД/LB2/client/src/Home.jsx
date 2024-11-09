import React, {useState} from 'react';
import {
    Box,
    Button,
    Container,
    Paper,
    Table, TableBody, TableCell,
    TableContainer,
    TableRow,
    TextField,
} from "@mui/material";
import MyTable from "./Table";

function Home() {
    const clientHeaders = ["id", "full_name", "passport", "phone"];
    const diskHeaders = ["id", "rental_cost", "quantity", "state"];
    const filmHeaders = ["id", "name", "genre", "year"];
    const orderHeaders = ["id", "time_get", "time_out", "sum","client_id"];

    const [searchInput, setSearchInput] = useState("")
    const [data, setData] = useState([]);

    const queryRequest = () => {
        fetch(`/query?query=${encodeURIComponent(searchInput)}`)
            .then(response => response.json())
            .then(data => setData(data))
            .catch(error => console.error('Ошибка:', error));
    }

    return (
        <Box>
            <Container>
                <Box
                    sx={{margin: "50px 0", display: "flex", gap: "20px", alignItems: "start", flexDirection: "column"}}>
                    <TextField sx={{width: "100%"}} onChange={(e) => setSearchInput(e.target.value)} fullWidth
                               label="Свой запрос" id="fullWidth"/>
                    <Button onClick={queryRequest} sx={{height: "40px", width: 100}} variant="contained"
                            color="success">
                        клац
                    </Button>
                    <TableContainer sx={{margin:"20px 0"}} component={Paper}>
                        <Table sx={{minWidth: 650}} aria-label="simple table">
                            <TableBody>
                                {data.map((row, rowIndex) => (
                                    <TableRow key={rowIndex}>
                                        {Object.values(row).map((cell, cellIndex) => (
                                            <TableCell key={cellIndex}>{cell}</TableCell>
                                        ))}
                                    </TableRow>
                                ))}
                            </TableBody>
                        </Table>
                    </TableContainer>
                </Box>
                <Box sx={{display: "flex", flexDirection: "column", gap: "20px"}}>
                    <MyTable title={"Список клиентов"} request={"/client"} headers={ clientHeaders }/>
                    <MyTable title={"Список фильмов"} request={"/film"} headers={ filmHeaders }/>
                    <MyTable title={"Список дисков"} request={"/disks"} headers={ diskHeaders }/>
                    <MyTable title={"Список заказов"} request={"/orders"} headers={ orderHeaders }/>
                </Box>
            </Container>
        </Box>
    );
}
export default Home;
