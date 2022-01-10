import firebase from 'firebase';

const firebaseConfig = {
  apiKey: "AIzaSyBoexAmZSTYXPaikHub9Pggocd-xHg5Dhk",
  authDomain: "fourth-ir-protection.firebaseapp.com",
  projectId: "fourth-ir-protection",
  storageBucket: "fourth-ir-protection.appspot.com",
  messagingSenderId: "1084166415231",
  appId: "1:1084166415231:web:0e15473583ef20ee7e704a",
  measurementId: "G-STWHHE5MPE"
};

// Initialize Firebase
firebase.initializeApp(firebaseConfig);

export default firebase;