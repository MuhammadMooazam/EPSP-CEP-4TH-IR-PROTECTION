import './App.css';
import GetData from './components/GetData';
import SendData from './components/SendData';
import { getList } from './components/GetData';

function App() {
  return (
    <div className="App">
      <h1>ELECTRICAL POWER SYSTEM PROTECTION</h1>
      <h2>FOURTH INDUSTRIAL REVOLUTION PROTECTION SYSTEM</h2>
      <h2>SENDING FAULT VALUES</h2>
      <SendData />
      <h2>GETTING FAULT TYPE</h2>
      <GetData />
    </div>
  );
}

export default App;
