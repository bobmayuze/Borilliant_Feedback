// angulat.module("BlankApp")
// var myApp = 
var myApp = angular.module('BlankApp', []);
myApp.controller('My_Controller', ['$scope', '$http', function($scope, $http) {
    console.log("Hello World from controller");
}]);
