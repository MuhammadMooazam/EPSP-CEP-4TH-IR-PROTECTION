import { useState } from "react";
import firebase from "../firebase";

function SendData() {
  const [phase1_current_magnitude, setphase1_current] = useState(0);
  const [phase2_current_magnitude, setphase2_current] = useState(0);
  const [phase3_current_magnitude, setphase3_current] = useState(0);
  const [phase1_current_angle, setphase1_current_angle] = useState(0);
  const [phase2_current_angle, setphase2_current_angle] = useState(0);
  const [phase3_current_angle, setphase3_current_angle] = useState(0);
  const [phase1_voltage_magnitude, setphase1_voltage] = useState(0);
  const [phase2_voltage_magnitude, setphase2_voltage] = useState(0);
  const [phase3_voltage_magnitude, setphase3_voltage] = useState(0);
  const [phase1_voltage_angle, setphase1_voltage_angle] = useState(0);
  const [phase2_voltage_angle, setphase2_voltage_angle] = useState(0);
  const [phase3_voltage_angle, setphase3_voltage_angle] = useState(0);
  // const [Fault_type, setFault_type] = useState(0);


  const sendData = () => {
    const sendDataRef = firebase.database().ref('input');
    const data = {
      // int: Number(int),
      // float: Number(float)
      phase1_voltage_magnitude: Number(phase1_voltage_magnitude),
      phase1_voltage_angle: Number(phase1_voltage_angle),
      phase2_voltage_magnitude: Number(phase2_voltage_magnitude),
      phase2_voltage_angle: Number(phase2_voltage_angle),
      phase3_voltage_magnitude: Number(phase3_voltage_magnitude),
      phase3_voltage_angle: Number(phase3_voltage_angle),
      phase1_current_magnitude: Number(phase1_current_magnitude),
      phase1_current_angle: Number(phase1_current_angle),
      phase2_current_magnitude: Number(phase2_current_magnitude),
      phase2_current_angle: Number(phase2_current_angle),
      phase3_current_magnitude: Number(phase3_current_magnitude),
      phase3_current_angle: Number(phase3_current_angle)
      // Fault_type: String(Fault_type)
    };

    sendDataRef.set(data);
  };
  return (
    <div>
      <h6>Enter Phase 1 Voltage Magnitude</h6>
      <input type="number" value={phase1_voltage_magnitude} onChange={(e) => setphase1_voltage(e.target.value)} placeholder="Enter Int Value" />
      <h6>Enter Phase 1 Voltage Angle</h6>
      <input type="number" value={phase1_voltage_angle} onChange={(e) => setphase1_voltage_angle(e.target.value)} placeholder="Enter Int Value" />
      <h6>Enter Phase 2 Voltage Magnitude</h6>
      <input type="number" value={phase2_voltage_magnitude} onChange={(e) => setphase2_voltage(e.target.value)} placeholder="Enter Int Value" />
      <h6>Enter Phase 2 Voltage Angle</h6>
      <input type="number" value={phase2_voltage_angle} onChange={(e) => setphase2_voltage_angle(e.target.value)} placeholder="Enter Int Value" />
      <h6>Enter Phase 3 Voltage Magnitude</h6>
      <input type="number" value={phase3_voltage_magnitude} onChange={(e) => setphase3_voltage(e.target.value)} placeholder="Enter Int Value" />
      <h6>Enter Phase 3 Voltage Angle</h6>
      <input type="number" value={phase3_voltage_angle} onChange={(e) => setphase3_voltage_angle(e.target.value)} placeholder="Enter Int Value" />
      <h6>Enter Phase 1 Current Magnitude</h6>
      <input type="number" value={phase1_current_magnitude} onChange={(e) => setphase1_current(e.target.value)} placeholder="Enter Int Value" />
      <h6>Enter Phase 1 Current Angle </h6>
      <input type="number" value={phase1_current_angle} onChange={(e) => setphase1_current_angle(e.target.value)} placeholder="Enter Int Value" />
      <h6>Enter Phase 2 Current Magnitude </h6>
      <input type="number" value={phase2_current_magnitude} onChange={(e) => setphase2_current(e.target.value)} placeholder="Enter Float Value" />
      <h6>Enter Phase 2 Current Angle  </h6>
      <input type="number" value={phase2_current_angle} onChange={(e) => setphase2_current_angle(e.target.value)} placeholder="Enter Int Value" />
      <h6>Enter Phase 3 Current Magnitude  </h6>
      <input type="number" value={phase3_current_magnitude} onChange={(e) => setphase3_current(e.target.value)} placeholder="Enter Int Value" />
      <h6>Enter Phase 3 Current Angle </h6>
      <input type="number" value={phase3_current_angle} onChange={(e) => setphase3_current_angle(e.target.value)} placeholder="Enter Int Value" />
      <br /><br />
      <button onClick={sendData}>Send Data</button>
    </div>
  )
}

export default SendData
