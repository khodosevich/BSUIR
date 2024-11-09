import React, {useEffect, useState} from 'react';
import {Box, Button, Table, Paper, TableBody, TableCell, TableContainer, TableHead, TableRow, Typography, Pagination} from "@mui/material";

const MyTable = ({title, request, headers}) => {

    const [tableData, setTableData] = useState([]);
    const [currentPage, setCurrentPage] = useState(1);
    const [tableVisible, setTableVisible] = useState(false);

    const itemsPerPage = 10;

    const currentData = tableData.slice((currentPage - 1) * itemsPerPage, currentPage * itemsPerPage);

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
        if (tableVisible) fetchTable();
    }, [tableVisible]);

    const handlePageChange = (event, value) => {
        setCurrentPage(value);
    };

    return (
        <Box sx={{width:"100%"}}>
            <Typography variant="h4">{title}</Typography>
            <Button sx={{marginTop:"10px"}} variant="contained" onClick={toggleOpen}>
                {tableVisible ? 'Свернуть' : 'Развернуть'}
            </Button>

            {
                tableVisible &&
                <>
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
                                    currentData.map(item => (
                                        <TableRow key={item.id}>
                                            {headers.map(header => (
                                                <TableCell key={header}>{item[header]}</TableCell>
                                            ))}
                                        </TableRow>
                                    ))
                                }
                            </TableBody>
                        </Table>
                    </TableContainer>

                    <Pagination
                        count={Math.ceil(tableData.length / itemsPerPage)}
                        page={currentPage}
                        onChange={handlePageChange}
                        color="primary"
                        sx={{display: 'flex', justifyContent: 'center', marginTop: '20px'}}
                    />
                </>
            }
        </Box>
    );
};

export default MyTable;