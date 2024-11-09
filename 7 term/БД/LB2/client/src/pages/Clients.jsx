import React from 'react';
import { Box } from "@mui/material";
import MyTable from "../Table";

const Clients = () => {
    const clientHeaders = ["id", "full_name", "passport", "phone"];

    return (
        <Box>
            <MyTable title={"Список клиентов"} request={"/client"} headers={ clientHeaders }/>
        </Box>
    );
};

export default Clients;