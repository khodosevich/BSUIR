import React from 'react';
import {Box, Container, CssBaseline, Typography} from "@mui/material";
import MyNavLink from "./MyNavLink";
import MyTable from "../Table";

const Laba5 = () => {
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
                        LB5
                    </Typography>
                    <Box display={"flex"} gap={2} flexDirection={"column"} marginTop={2}>
                        <MyTable request={'/order-sum'} title={"Вывести сумму всех заказов"} headers={["total_sum"]}/>
                        <MyTable request={'/avg'} title={"Вывести среднюю стоимость дисков."} headers={["average_cost"]}/>
                        <MyTable request={'/client-count'} title={"Вывести количество клиентов"} headers={["client_count"]}/>
                    </Box>
                </Box>
            </Container>
        </Box>
    );
};

export default Laba5;