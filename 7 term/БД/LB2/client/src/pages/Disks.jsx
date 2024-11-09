import React from 'react';
import MyTable from "../Table";
import {Box} from "@mui/material";

const Disks = () => {
    const diskHeaders = ["id", "rental_cost", "quantity", "state"];

    return (
        <Box>
            <MyTable title={"Список дисков"} request={"/disks"} headers={ diskHeaders }/>
        </Box>
    );
};

export default Disks;