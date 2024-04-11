import React from 'react';
import {NavLink} from "react-router-dom";

const MyNavLink = ({link,name}) => {
    return (
        <NavLink style={{
            color:"black",
            textDecoration:"none",
            textTransform: "uppercase",
            padding:"10px 50px",
            background:"#dcdcdc",
            borderRadius:"20px"
        }} to={link}>
            {name}
        </NavLink>
    );
};

export default MyNavLink;