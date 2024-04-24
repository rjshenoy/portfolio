// Imports the server.js file to be tested.
const server = require("../server");
// Assertion (Test Driven Development) and Should,  Expect(Behaviour driven 
// development) library
const chai = require("chai");
// Chai HTTP provides an interface for live integration testing of the API's.
const chaiHttp = require("chai-http");
const { request } = require("chai");
const { json } = require("body-parser");
chai.should();
chai.use(chaiHttp);
const { assert, expect } = chai;

describe("Server!", () => {
  // Sample test case given to test / endpoint.
  it("Returns the default welcome message", (done) => {
    chai
      .request(server)
      .get("/")
      .end((err, res) => {
        expect(res).to.have.status(200);
        expect(res.body.status).to.equals("success");
        assert.strictEqual(res.body.message, "Welcome!");
        done();
      });
  });

  // ===========================================================================
  // TODO: Please add your test cases for part A here.

    describe("Test op", () => {

      it("Get test for op", (done) => {

        chai
          .request(server)
          .get("/operations")
          .end((err, res) => {

              expect(res).to.have.status(200);
              expect(res.body).to.be.an('array');
              assert.should.not.be.equals(res.body.length,0);
              done();

          });


      });

    });


      describe("Test op id", () => {

        it("Get test for op id", (done) => {

          chai
            .request(server)
            .get("/operations")
            .end((err, res) => {
  
                expect(res).to.have.status(200);
                expect(res.body[0]).to.have.property("name");
                expect(res.body[0]).to.have.property("id",1);
                expect(res.body[0]).to.have.property("sign");
                // assert.should.be.equals(res.body.length,1);
                
                done();
  
            });
  
        });
  
  
      });

      
      



      describe("Test op post", () => {

        it("Post test for op", (done) => {

          chai
            .request(server)
            .post("/operations")
            .send({name:"division", sign:"/"})            

            .end((err, req) => {
  
                expect(req).to.have.status(201);
                

                console.log(req.body);

                expect(req.body).to.have.property("name", "division");
                expect(req.body).to.have.property("id",4);
                expect(req.body).to.have.property("sign", "/");
                // assert.should.be.equals(res.body.length,1);
                
                done();
  
            });
  
        });
  
  
      });

      

     
  // ===========================================================================
  // TODO: Please add your test cases for part B here.

  // Pt 1

  function sum(num1, num2){
    if(isNaN(num1,num2)){
      return NaN;
    }
    else return num1 + num2;
  }

  describe("/post for /add", () => {
    it("adds numbers success", (done) => {
      let num = {num1: 9, num2: 10};
      chai
        .request(server)
        .post("/add")
        .send(JSON.stringify(sum))
        .end((err,res) => {
          expect(res).to.have.status(201);
          expect(res.body).to.have.property('num1');
          expect(res.body).to.have.property('num2');
          done();
        });
    });
    it("non-numbers fail", (done) => {
      let num = {num1: 'one', num2: 'two'};
      chai
        .request(server)
        .post("/add")
        .send(JSON.stringify(num.num1+num.num2))
        .end((err,res) => {
          expect(sum(num.num1,num.num2)).to.be.NaN;
          done();
        });
    });
  });

  //Pt 2

  function quotient(num1, num2){
    if(isNaN(num1,num2) || num2 == 0){
      return NaN;
    }
    else return num1 + num2;
  }

  describe("/POST to /divide", () => {
    it("divide success", (done) => {
      let num = {num1: 18, num2: 9};
      chai
        .request(server)
        .post("/divide")
        .send(JSON.stringify(num.num1/num.num2))
        .end((err,res) => {
          expect(res).to.have.status(201);
          expect(res.body).to.have.property('num1');
          expect(res.body).to.have.property('num2');
          done();
        });
    });
    it("divide fail", (done) => {
      let num = {num1: 11, num2: 0};
      chai
        .request(server)
        .post("/divide")
        .send(JSON.stringify(quotient))
        .end((err,res) => {
          console.log(res.body);
          expect(quotient(num.num1,num.num2)).to.be.NaN;
          done();
        });
    });
  });
});