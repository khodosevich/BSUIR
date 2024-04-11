import React from 'react';
import {Box, Container, CssBaseline, Typography} from "@mui/material";
import MyNavLink from "./MyNavLink";
import MyTable from "../Table";

const Laba4 = () => {
    return (
        <Box>
            <CssBaseline/>
            <Container>
                <Box sx={{
                    marginTop:"20px"
                }}>
                    <MyNavLink link={"/"} name={"Главная"}/>
                </Box>
                <Box>
                    <Typography sx={{marginTop:"20px"}} variant="h4">
                        LB4
                    </Typography>
                    <Box display={"flex"} gap={2} flexDirection={"column"} marginTop={2}>
                        <MyTable request={'/like'} title={"Вывести клиента с фамилией, которая начинается на “Kho”"} headers={["full_name", "phone"]}/>
                        <MyTable request={'/genre'} title={"Вывести все фильмы вышедшие после 01.01.2000 года, жанр боевик"} headers={["name", "year","genre"]}/>
                        <MyTable request={'/client-order'} title={"Вывести полное имя клиента сумму заказа клиента, время выдачи и сдачи заказа, сумма заказа от 10 до 30"} headers={["full_name", "sum","time_get","time_out"]}/>
                    </Box>
                </Box>
            </Container>
        </Box>
    );
};

export default Laba4;