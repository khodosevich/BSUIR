import React, {useState} from 'react';
import {
    Box,
    Button,
    Container,
    CssBaseline,
    Paper,
    Table, TableBody, TableCell,
    TableContainer,
    TableRow,
    TextField,
} from "@mui/material";
import MyTable from "./Table";
import MyNavLink from "./components/MyNavLink";

function Home() {

    const clientHeaders = ["id", "full_name", "passport", "phone"];
    const diskHeaders = ["id", "rental_cost", "quantity", "state"];
    const filmHeaders = ["id", "name", "genre", "year","director_id"];
    const orderHeaders = ["id", "time_get", "time_out", "sum","client_id"];
    const reviewHeaders = ["id", "mark", "comment", "client_id","film_id"];

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
                <CssBaseline/>
                <Box sx={{
                    display:"flex",
                    gap:"20px",
                    width:"100%",
                    margin:"30px 0",
                }}>
                    <MyNavLink link={"/laba4"} name={"lb4"}/>
                    <MyNavLink link={"/laba5"} name={"l54"}/>
                </Box>

                <Box
                    sx={{margin: "50px 0", display: "flex", gap: "20px", alignItems: "start", flexDirection: "column"}}>
                    <TextField sx={{width: 400}} onChange={(e) => setSearchInput(e.target.value)} fullWidth
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
                    <MyTable title={"Список клиентов"} request={"/client"} headers={clientHeaders}/>
                    <MyTable title={"Список дисков"} request={"/disks"} headers={diskHeaders}/>
                    <MyTable title={"Список фильмов"} request={"/film"} headers={filmHeaders}/>
                    <MyTable title={"Список отзывов"} request={"/reviews"} headers={reviewHeaders}/>
                    <MyTable title={"Список заказов"} request={"/orders"} headers={orderHeaders}/>
                </Box>
            </Container>
        </Box>
    );
}
export default Home;
