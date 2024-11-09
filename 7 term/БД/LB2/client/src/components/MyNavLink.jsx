import React from 'react';
import {NavLink} from "react-router-dom";

const MyNavLink = ({link, name }) => {
    return (
        <NavLink
            to={link}
            style={({ isActive }) => ({
                color: isActive ? "orange" : "black",
                textDecoration: "none",
                fontSize: "20px",
                fontWeight: isActive ? "bold" : "normal",
            })}
        >
            {name}
        </NavLink>
    );
};

export default MyNavLink;