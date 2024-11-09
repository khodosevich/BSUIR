import React from 'react';
import { Box } from "@mui/material";
import MyTable from "../Table";

const Orders = () => {
    const orderHeaders = ["id", "time_get", "time_out", "sum","client_id"];

    return (
        <Box>
            <MyTable title={"Список заказов"} request={"/orders"} headers={ orderHeaders }/>
        </Box>
    );
};

export default Orders;