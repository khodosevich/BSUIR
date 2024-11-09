import React from 'react';
import {Box} from "@mui/material";
import MyTable from "../Table";

const Films = () => {
    const filmHeaders = ["id", "name", "genre", "year"];

    return (
        <Box>
            <MyTable title={"Список фильмов"} request={"/film"} headers={ filmHeaders }/>
        </Box>
    );
};

export default Films;