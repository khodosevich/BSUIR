import React, {useEffect, useState} from 'react';
import {Box, Button, Table, Paper, TableBody, TableCell, TableContainer, TableHead, TableRow, Typography} from "@mui/material";

const MyTable = ({title, request, headers}) => {

    const [tableData, setTableData] = useState([]);
    const [tableVisible, setTableVisible] = useState(false);

    const fetchTable = () => {
        fetch(request)
            .then(response => response.json())
            .then(data => setTableData(data))
            .catch(error => console.error('Ошибка:', error));
    }

    const toggleOpen = () => {
        setTableVisible(!tableVisible);
    };

    useEffect(() => {
        if (tableVisible)
            fetchTable();
    },[tableVisible])

    return (
        <Box sx={{width:"100%"}}>
            <Typography>{title}</Typography>
            <Button sx={{marginTop:"10px"}} variant="contained" onClick={toggleOpen}>{tableVisible ? 'Свернуть' : 'Развернуть'}</Button>
            {
                tableVisible &&
                <TableContainer sx={{margin:"20px 0"}} component={Paper}>
                    <Table sx={{minWidth: 650}} aria-label="simple table">
                        <TableHead>
                            <TableRow>
                                {headers.map(header => (
                                    <TableCell key={header}>{header}</TableCell>
                                ))}
                            </TableRow>
                        </TableHead>
                        <TableBody>
                            {
                                tableData.map(item => (
                                    <TableRow
                                        key={item.id}
                                    >
                                        {headers.map(header => (
                                            <TableCell key={header}>{item[header]}</TableCell>
                                        ))}
                                    </TableRow>
                                ))
                            }
                        </TableBody>
                    </Table>
                </TableContainer>
            }
        </Box>
    );
};

export default MyTable;