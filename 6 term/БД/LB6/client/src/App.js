import React from 'react';
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';
import Home from './Home';
import Laba4 from "./components/Laba4";
import Laba5 from "./components/Laba5";

function App() {
    return (
        <Router>
            <Routes>
                <Route path="/" element={<Home/>} />
                <Route path="/laba4" element={<Laba4/>} />
                <Route path="/laba5" element={<Laba5/>} />
            </Routes>
        </Router>
    );
}

export default App;
