import React from 'react';
import {BrowserRouter as Router, Route, Routes} from 'react-router-dom';
import Home from './Home';
import {Box, Container, CssBaseline} from "@mui/material";
import MyNavLink from "./components/MyNavLink";
import Clients from "./pages/Clients";
import Films from "./pages/Films";
import Disks from "./pages/Disks";
import Orders from "./pages/Orders";

function App() {
    return (
        <Router>
            <CssBaseline/>
            <Container>
                <Box sx={{display: "flex", gap: "20px", paddingBlock: 2, justifyContent: "center"}}>
                    <MyNavLink link='/' name='Главная'/>
                    <MyNavLink link='/films' name='Фильмы'/>
                    <MyNavLink link='/clients' name='Клиенты'/>
                    <MyNavLink link='/disks' name='Диски'/>
                    <MyNavLink link='/orders' name='Заказы'/>
                </Box>

                <Routes>
                    <Route path="/" element={<Home/>} />
                    <Route path="/clients" element={<Clients />} />
                    <Route path="/films" element={<Films />} />
                    <Route path="/disks" element={<Disks/>} />
                    <Route path="/orders" element={<Orders/>} />
                </Routes>
            </Container>
        </Router>
    );
}

export default App;
